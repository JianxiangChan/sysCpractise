/*
 * File:    darray.c
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   dynamic array implementation.
 *
 * Copyright (c) Li XianJing
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-01-02 Li XianJing <xianjimli@hotmail.com> created
 * ================================================================
 *	2017-05-17 Jianxiang Chan<15651898806@163.com>modified
 */
 
 #include <stdlib.h>
 #include "darray.h"
 
 struct _DArray
 {
	 void **data;
	 size_t size;
	 size_t alloc_size;
	 
	 void* data_destroy_ctx;
	 DataDestroyFunc data_destroy;
 };
 
 static void darray_destory_data(DArray* thiz, void* data)
 {
	 if(NULL !=thiz->data_destroy)
	 {
		 thiz->data_destroy(thiz->data_destroy_ctx, data);
	 }
	 
	 return;
 }
 
 DArray* darray_creat(DataDestroyFunc data_destroy, void *ctx)
 {
	 DArray* thiz = malloc(sizeof(DArray));
	 if(NULL != thiz)
	 {
		 thiz->data = NULL;
		 thiz->size = 0;
		 thiz->alloc_size = 0;
		 thiz->data_destroy = data_destroy;
		 thiz->data_destroy_ctx = ctx;
	 }
	 
	 return thiz;
 }
 
 #define MIN_PRE_ALLOCATE_NR 10
 static Ret darray_expand(DArray* thiz, size_t need)
 {
	 return_val_if_fail(NULL != thiz, RET_INVALID_PARAMS);
	 if((thiz->size + need) > thiz->alloc_size)		//需要增加数组
	 {
		 //1.5*thiz->alloc_size+10
		 size_t alloc_size = thiz->alloc_size + (thiz->alloc_size >> 1) + MIN_PRE_ALLOCATE_NR;
		 
		 void**  data = (void **)realloc(thiz->data,sizeof(void *) * alloc_size);
		 if(NULL != data)
		 {
			 //存指针
			 thiz->data = data;
			 thiz->alloc_size = alloc_size;
		 }
	 }
	  return ((thiz->size +need) <= thiz->alloc_size) ? RET_OK : RET_FAIL;
 }
 
 static Ret darray_shrink(DArray* thiz)
 {
	 return_val_if_fail(NULL != thiz, RET_INVALID_PARAMS);
	 
	 if((thiz->size < (thiz->alloc_size >> 1)) && (thiz->alloc_size > MIN_PRE_ALLOCATE_NR))
	 {
		 size_t alloc_size = thiz->size + (thiz->size >> 1);
		 
		 void** data = (void**)realloc(thiz->data, sizeof(void *)*alloc_size);
		 if(NULL != data)
		 {
			thiz->data =data;
			thiz->alloc_size = alloc_size;
		 }
	 }
 }
 
 Ret darray_insert(DArray* thiz, size_t index, void* data)
 {
	 Ret ret = RET_OOM;
	 size_t cursor = index;
	 return_val_if_fail(NULL != thiz, RET_INVALID_PARAMS);
	 
	 //防止越界
	 cursor = cursor < thiz->size ? cursor : thiz->size;
	 if(RET_OK == darray_expand(thiz,1))
	 {
		 size_t i = 0;
		 for(i = thiz->size; i>cursor; i--)
		 {
			 thiz->data[i] = thiz->data[i-1];
		 }
		 
		 thiz->data[cursor] = data;
		 thiz->size++;
		 
		 ret = RET_OK;
	 }
	 
	 return ret;
 }
 
 Ret darray_prepend(DArray* thiz, void* data)
 {
	 return darray_insert(thiz, 0, data);
 }
 
 Ret darray_append(DArray* thiz, void* data)
 {
	 return darray_insert(thiz, -1, data);
 }
 
 Ret darray_delete(DArray* thiz, size_t index)
 {
	 size_t i = 0;
	 Ret ret = RET_OK;
	 
	 return_val_if_fail(NULL != thiz, RET_INVALID_PARAMS);
	 
	 darray_destory_data(thiz, thiz->data[index]);
	 for(i = index; (i+1) < thiz->size; i++)
	 {
		 thiz->data[i] = thiz->data[i+1];
	 }
	 thiz->size--;
	 
	 darray_shrink(thiz);
	 
	 return ret;
	 
 }
 
 Ret darray_get_by_index(DArray* thiz,size_t index, void** data)
 {
	 return_val_if_fail(NULL != thiz && NULL != data && index < thiz->size, 
		RET_INVALID_PARAMS);
		
	*data = thiz->data[index];
	
	return RET_OK;
 }
 
 Ret darray_set_by_index(DArray* thiz, size_t index, void* data)
 {
	  return_val_if_fail(NULL != thiz && index < thiz->size, 
		 RET_INVALID_PARAMS);


	thiz->data[index] = data;
	
	return RET_OK;
 }
 
 size_t darray_length(DArray* thiz)
 {
	 size_t length = 0;
	 
	 return_val_if_fail(thiz != NULL, 0);
	 return thiz->size;
 }
 
 Ret darray_foreach(DArray* thiz, DataVisitFunc visit, void* ctx)
 {
	 size_t i= 0;
	 Ret ret = RET_OK;
	 return_val_if_fail(thiz != NULL && NULL != visit,RET_INVALID_PARAMS);
	 
	 for(i = 0; i < thiz->size; i++)
	 {
		 ret = visit(ctx,thiz->data[i]);
	 }
	 return ret;
 }
 
 //ctx不能初始化为等于第一个元素的值，否则回漏打第一个数。
  Ret unique_print_int(void* ctx, void* data)
 {
	 if(*(int *)ctx != (int)data)
	 {
		 *(int *)ctx = (int)data;
		 printf("%d ",(int)data);
	 }
 }
 int darray_find(DArray* thiz, DataCompareFunc cmp, void* ctx)
 {
	 size_t i = 0;
	 
	 return_val_if_fail(NULL != thiz && NULL != cmp, -1);
	 
	 for(i = 0; i< thiz->size; i++)
	 {
		 if(0 == cmp(ctx, thiz->data[i]))
		 {
			 break;
		 }
	 }
	 return i ;
 }
 
 void darray_destory(DArray* thiz)
 {
	 size_t i = 0;
	 if(NULL != thiz)
	 {
			 for(i = 0; i < thiz->size; i++)
			 {
				darray_destory_data(thiz, thiz->data[i]) ;
			 }
			 
			SAFE_FREE(thiz->data);
			SAFE_FREE(thiz);
	 }
		
	return;
 }
 
 Ret bubble_sort(void** array, size_t nr, DataCompareFunc cmp)
 {
	 size_t right = 0;
	 size_t max = 0;
	 size_t i = 0;
	 void* data = 0;
	 
	 return_val_if_fail(NULL != array && NULL != cmp
			, RET_INVALID_PARAMS);
			
	if(nr < 2)
	{
		return RET_OK;
	}
	
	for(right = nr -1; right >0; right --)
	{
		for(i = 0, max = 0; i<right; i++)
		{
			if(cmp(array[i],array[max]) > 0)
			{
				max = i;
			}
		}
		if(cmp(array[max], array[right]) > 0)
		{
			data = array[max];
			array[max] = array[right];
			array[right] = data;
		}
	}
	return RET_OK;
 }
 
 static void quick_sort_impl(void** array, size_t left, size_t right, DataCompareFunc cmp)
 {
	 size_t save_left = left;
	 size_t save_right = right;
	 void* x = array[left];
	 while(left < right)
	 {
		 while(cmp(array[right], x) >= 0 && left < right) right--;
		 if(left != right)
		 {
			array[left] = array[right];
			left++;
		 }
		 while(cmp(array[left], x) <= 0 && left < right) left++;
		 if(left != right)
		 {
			 array[right] = array[left];
			 right--;
		 }
	 }
	 array[left] = x;
	 if(save_left < left)
	 {
		quick_sort_impl(array, save_left, left - 1, cmp);
	 }
	 if(save_right > right)
	 {
		 quick_sort_impl(array, left+1, save_right, cmp);
	 }
	 return; 
 }
 
 Ret quick_sort(void** array, size_t nr, DataCompareFunc cmp)
 {
	 Ret ret = RET_OK;
	 
	 return_val_if_fail(NULL != array && NULL != cmp, RET_INVALID_PARAMS);
	 
	 if(nr >1)
	 {
		 quick_sort_impl(array, 0, nr-1, cmp);
	 }
	 
	 return ret;
 }
 
 static Ret merge_sort_impl(void** storage, void** array, size_t low, size_t mid,
							size_t high, DataCompareFunc cmp)
 {
	 size_t i = low;
	 size_t j = low;
	 size_t k = mid;
	 if((low + 1) < mid)
	 {
		 size_t x = low + ((mid - low) >> 1);	//这里在写的时候忘记了大括号 导致优先级运行错误  所以程序死在这里 可怕的BUG!!!
		 merge_sort_impl(storage, array, low, x, mid, cmp);
	 }
	 if((mid + 1) < high)
	 {

		 size_t x = mid + ((high - mid) >> 1);
		 merge_sort_impl(storage, array, mid, x, high, cmp);
	 }
	 	
	 while(j < mid && k <high)
	 {
		 if(cmp(array[j], array[k]) <= 0)
		 {
			 storage[i++] = array[j++];
		 }
		 else
		 {
			 storage[i++] = array[k++];
		 }
	 }

	 while(j < mid)
	 {
		 storage[i++] = array[j++];
	 }
	 while(k < high)
	 {
		 storage[i++] = array[k++];
	 }
	 for(i = low; i< high; i++)
	 {
		 array[i] = storage[i];
	}
	 return RET_OK;
 }
 
 Ret merge_sort(void ** array, size_t nr, DataCompareFunc cmp)
 {
	 void ** storage = NULL;
	 Ret ret = RET_OK;
	 
	 return_val_if_fail(NULL != array && NULL != cmp, RET_INVALID_PARAMS);
	 
	 if(nr > 1)
	 {
		 storage = (void**)malloc(sizeof(void *) * nr);
		 if(NULL != storage)
		 {
			 ret = merge_sort_impl(storage, array, 0, nr>>1, nr, cmp);
			 SAFE_FREE(storage);
		 }
	 }
	 return ret;
 }
 Ret darray_sort(DArray* thiz, SortFunc sort, DataCompareFunc cmp)
 {
	 return sort(thiz->data, thiz->size, cmp);
 }
 
 int qsearch(void** array, size_t nr, void* data, DataCompareFunc cmp)
 {
	 int low = 0;
	 int high = nr - 1;
	 int mid = 0;
	 int result = 0;
	 return_val_if_fail(NULL != array && NULL != cmp, -1);
	 while(low == high)
	 {
		 //mid = (high - low) >> 2; 需要考虑low不为0的情况
		 //mid = low + ((high - low) >> 2);这个也是错的
		 //这样写可以避免溢出和除法运算
		 mid = low + ((high - low) >> 1);
		 result = cmp(data, array[mid]);
		 if(result == 0)
		 {
			 return mid;
		 }
		 else if(result >0)
		 {
			 low = mid + 1;
		 }
		 else
		 {
			 high = mid - 1;
		 }
	 }
	 return -1;
 }
 
 #ifdef DARRAY_TEST
 
 #include <assert.h>
 
 static int int_cmp(void* ctx, void* data)
 {
	 return (int)ctx - (int)data;
 }
 
 static int_cmp_reverse(void* ctx, void* data)
 {
	 return (int)data - (int)ctx;
 }
 
 static Ret int_print(void* ctx, void* data)
 {
	printf("%d\n", (int)data);
	return RET_OK;
 }
 
 static Ret check_and_dec_int(void* ctx, void* data)
 {
	 int* expected = (int *)ctx;
	 assert(*expected == (int)data);
	 
	 (*expected)--;
	 
	 return RET_OK;
 }
 
 static void test_int_darray(void)
 {
	int i = 0;
	int n = 100;
	int data = 0;
	DArray* darray = darray_creat(NULL,NULL);
	
	for(i = 0; i<n; i++)
	{
		//printf("i = %d.\n", i);
		assert(darray_append(darray, (void*)i) == RET_OK);
		assert(darray_length(darray) == (i+1));
		assert(darray_get_by_index(darray, i, (void**)&data) == RET_OK);
		assert(data == i);
		assert(darray_set_by_index(darray, i, (void*)(2*i)) == RET_OK);
		assert(darray_get_by_index(darray, i, (void**)&data) == RET_OK);
		assert(data == 2*i);
		assert(darray_set_by_index(darray, i, (void*)i) == RET_OK);
		assert(darray_find(darray, int_cmp, (void*)i) == i);
	}
	
	for(i=0; i<n; i++)
	{
		assert(darray_get_by_index(darray, 0, (void**)&data) == RET_OK);
		assert(data == (i));
		assert(darray_length(darray) == (n-i));
		assert(darray_delete(darray, 0) == RET_OK);
		assert(darray_length(darray) == (n-i-1));
		if((i+1) < n)
		{
			assert(darray_get_by_index(darray, 0, (void**)&data) == RET_OK);
			assert((int)data == (i+1));
		}
	}
	
	assert(darray_length(darray) == 0);
	
	for(i = 0; i<n; i++)
	{
		assert(darray_prepend(darray,(void*)i) == RET_OK);
		assert(darray_length(darray) == i+1);
		assert(darray_get_by_index(darray, 0, (void**)&data) == RET_OK);
		assert(data == i);
		assert(darray_set_by_index(darray, 0, (void*)(2*i)) == RET_OK);
		assert(darray_get_by_index(darray, 0, (void*)&data) == RET_OK);
		assert(data == 2*i);
		assert(darray_set_by_index(darray, 0, (void*)i) == RET_OK);
	}
	
	i = n - 1;
	assert(darray_foreach(darray, check_and_dec_int, &i) == RET_OK);
	darray_destory(darray);
	
	return;
 } 
 
 static void test_invalid_params(void)
 {
	 printf("===========Warning is normal begin==============\n");
	assert(darray_length(NULL) == 0);
	assert(darray_prepend(NULL, 0) == RET_INVALID_PARAMS);
	assert(darray_append(NULL, 0) == RET_INVALID_PARAMS);
	assert(darray_delete(NULL, 0) == RET_INVALID_PARAMS);
	assert(darray_insert(NULL, 0, 0) == RET_INVALID_PARAMS);
	assert(darray_set_by_index(NULL, 0, 0) == RET_INVALID_PARAMS);
	assert(darray_get_by_index(NULL, 0, NULL) == RET_INVALID_PARAMS);
	assert(darray_find(NULL, NULL, NULL) < 0);
	assert(darray_foreach(NULL, NULL, NULL) == RET_INVALID_PARAMS);
	printf("===========Warning is normal end==============\n");

	return; 
 }
 
 static void ** creat_int_array(int n)
 {
	int i = 0;
	int* array = (int*)malloc(sizeof(int) * n);
	for(i = 0; i < n; i++)
	{
		array[i] = rand();
	}
	return (void**)array;
 }
 
 static void sort_test_one_asc(SortFunc sort, int n)
 {
	 int i = 0;
	 void** array = creat_int_array(n);
	 sort(array, n, int_cmp);
	 for(i = 1; i < n; i++)
	 {
		 assert(array[i] >= array[i-1]);
	 }
	 
	 SAFE_FREE(array);
	 
	 return;
 }
 
 void sort_test(SortFunc sort)
 {
	int i = 0;
	for(i = 0; i < 1000; i++)
	{
		sort_test_one_asc(sort, i);
	}
 }
 
  void single_thread_test(void)
 {
	 test_int_darray();
	 test_invalid_params();
	 sort_test(quick_sort);
	 sort_test(merge_sort);
	 sort_test(bubble_sort);
	 
	 return;
 }
 
 #endif
