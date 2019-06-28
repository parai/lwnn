/**
 * LWNN - Lightweight Neural Network
 * Copyright (C) 2019  Parai Wang <parai@foxmail.com>
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "nn.h"
#ifndef DISABLE_RUNTIME_OPENCL
#include "runtime_opencl.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int layer_opencl_OUTPUT_init(const nn_t* nn, const layer_t* layer)
{
	int r = 0;

	return r;
}

int layer_opencl_OUTPUT_execute(const nn_t* nn, const layer_t* layer)
{
	int r = 0;

	return r;
}

int layer_opencl_OUTPUT_deinit(const nn_t* nn, const layer_t* layer)
{
	int r = 0;

	return r;
}

#endif /* DISABLE_RUNTIME_OPENCL */
