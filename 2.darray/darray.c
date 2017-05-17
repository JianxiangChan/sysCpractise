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
		 return ((thiz->size +need) <= thiz->alloc_size) ? RET_OK : RET_FAIL;
	 }
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
	 return_val_if_fail(NULL != thiz && NULL != data && index < thiz->size, 
		RET_INVALID_PARAMS);
		
	thiz->data[index] = data;
	
	return RET_OK;
 }
 
 size_t darray_length(DArray* thiz)
 {
	 size_t length = 0;
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
 }
 
 int darray_find(DArray* thiz, DataCompareFunc cmp, void* ctx)
 {
	 size_t i = 0;
	 
	 return_val_if_fail(NULL != thiz && NULL != cmp, -1);
	 
	 for
 }
 
 static void test_int_darray(void)
 {
	 
 } 
 
 static void test_invalid_params(void)
 {
	 
 }
 
 void single_thread_test(void)
 {
	 test_int_darray();
	 test_invalid_params();
	 
	 return;
 }