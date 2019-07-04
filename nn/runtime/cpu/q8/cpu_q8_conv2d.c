/**
 * LWNN - Lightweight Neural Network
 * Copyright (C) 2019  Parai Wang <parai@foxmail.com>
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "nn.h"
#ifndef DISABLE_RUNTIME_CPU_Q8
#include "../runtime_cpu.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
typedef struct {
	LAYER_CPU_CONTEXT_MEMBER;
} layer_cpu_q8_conv2d_context_t;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int layer_cpu_q8_CONV2D_init(const nn_t* nn, const layer_t* layer)
{
	int r = 0;

	layer_cpu_q8_conv2d_context_t* context;

	r = rte_cpu_create_layer_context(nn, layer,
				sizeof(layer_cpu_q8_conv2d_context_t), 0);

	if(0 == r)
	{
		context = (layer_cpu_q8_conv2d_context_t*)layer->C->context;

		RTE_CPU_LOG_LAYER_SHAPE(layer);
	}

	return r;
}

int layer_cpu_q8_CONV2D_execute(const nn_t* nn, const layer_t* layer)
{
	int r = 0;
	layer_cpu_q8_conv2d_context_t* context = (layer_cpu_q8_conv2d_context_t*)layer->C->context;
	const layer_t* input = layer->inputs[0];
	layer_cpu_context_t* input_context;
	int8_t* data;

	input_context = (layer_cpu_context_t*)input->C->context;

	NNLOG(NN_DEBUG, ("execute %s\n", layer->name));


	return r;
}

void layer_cpu_q8_CONV2D_deinit(const nn_t* nn, const layer_t* layer)
{
	rte_cpu_destory_layer_context(nn, layer);
}

#endif /* DISABLE_RUNTIME_CPU_Q8 */
