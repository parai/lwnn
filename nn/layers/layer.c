/**
 * LWNN - Lightweight Neural Network
 * Copyright (C) 2019  Parai Wang <parai@foxmail.com>
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "nn.h"
/* ============================ [ MACROS    ] ====================================================== */
#ifndef DISABLE_RTE_FALLBACK
#define FALLBACK_TEMPLATE(from, to, gf)													\
extern void rte_##gf##_to_##to##_init_common(const nn_t*, const layer_t*);				\
extern int rte_##gf##_to_##to##_pre_execute_common(const nn_t*, const layer_t*);		\
extern void rte_##gf##_to_##to##_post_execute_common(const nn_t*, const layer_t*);		\
void layer_##from##_to_##to##_init_common(const nn_t* nn, const layer_t* layer)			\
{																						\
	rte_##gf##_to_##to##_init_common(nn, layer);										\
}																						\
int layer_##from##_to_##to##_pre_execute_common(const nn_t* nn, const layer_t* layer)	\
{																						\
	return rte_##gf##_to_##to##_pre_execute_common(nn, layer);							\
}																						\
void layer_##from##_to_##to##_post_execute_common(const nn_t* nn, const layer_t* layer)	\
{																						\
	rte_##gf##_to_##to##_post_execute_common(nn, layer);								\
}
#else
#define FALLBACK_TEMPLATE(from, to, gf)
#endif
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int layer_get_blob_NHWC(const layer_blob_t* blob, NHWC_t* nhwc)
{
	int r = 0;
	int dim = 0;

	const int* dims = blob->dims;

	assert(dims != NULL);

	while((dims[dim] != 0) && (dim < 4)) {
		dim ++;
	};

	switch(dim)
	{
		case 1:
			nhwc->N = 1;
			nhwc->H = 1;
			nhwc->W = 1;
			nhwc->C = dims[0];
			break;
		case 2:
			nhwc->N = 1;
			nhwc->H = dims[0];
			nhwc->W = 1;
			nhwc->C = dims[1];
			break;
		case 3:
			nhwc->N = 1;
			nhwc->H = dims[0];
			nhwc->W = dims[1];
			nhwc->C = dims[2];
			break;
		case 4:
			nhwc->N = dims[0];
			nhwc->H = dims[1];
			nhwc->W = dims[2];
			nhwc->C = dims[3];
			break;
		default:
			NNLOG(NN_ERROR, ("invalid dimension of blob\n"));
			r = NN_E_INVALID_DIMENSION;
			break;
	}

	return r;
}

int layer_get_NHWC(const layer_t* layer, NHWC_t* nhwc)
{
	int r = 0;
	int dim = 0;
	const int* dims = layer->dims;

	assert(dims != NULL);

	while((dims[dim] != 0) && (dim < 4)) {
		dim ++;
	};

	switch(dim)
	{
		case 2:
			nhwc->N = dims[0];
			nhwc->H = 1;
			nhwc->W = 1;
			nhwc->C = dims[1];
			break;
		case 3:
			nhwc->N = dims[0];
			nhwc->H = dims[1];
			nhwc->W = 1;
			nhwc->C = dims[2];
			break;
		case 4:
			nhwc->N = dims[0];
			nhwc->H = dims[1];
			nhwc->W = dims[2];
			nhwc->C = dims[3];
			break;
		default:
			NNLOG(NN_ERROR, ("invalid dimension for %s\n", layer->name));
			r = NN_E_INVALID_DIMENSION;
			break;
	}

	return r;
}

size_t layer_get_size(const layer_t* layer)
{
	int dim = 0;
	size_t sz = 1;

	if(NULL != layer->C->context)
	{
		dim = 4;
		sz = NHWC_SIZE(layer->C->context->nhwc);
	}
	else if(NULL != layer->dims)
	{
		while(layer->dims[dim] != 0) {
			sz *= layer->dims[dim];
			dim ++;
		};
	}
	else
	{
		NNLOG(NN_ERROR, ("can't get %s layer size for now\n", layer->name));
	}

	if(0 == dim)
	{
		sz = 0;
	}

	return sz;
}

/* ============================ [ UNSUPPORTED/FALLBACK ] =========================================== */
UNSUPPORTED_LAYER_OPS(cpu_s8, CONST)
UNSUPPORTED_LAYER_OPS(cpu_q8, CONST)
UNSUPPORTED_LAYER_OPS(cpu_q16, CONST)

FALLBACK_LAYER_OPS(cpu_s8, DETECTIONOUTPUT, cpu_float)
FALLBACK_LAYER_OPS(cpu_q8, DETECTIONOUTPUT, cpu_float)
FALLBACK_LAYER_OPS(cpu_q16, DETECTIONOUTPUT, cpu_float)
FALLBACK_LAYER_OPS(cl, DETECTIONOUTPUT, cpu_float)


UNSUPPORTED_LAYER_OPS(cpu_s8, YOLO)
UNSUPPORTED_LAYER_OPS(cpu_q8, YOLO)
UNSUPPORTED_LAYER_OPS(cpu_q16, YOLO)
FALLBACK_LAYER_OPS(cl, YOLO, cpu_float)

UNSUPPORTED_LAYER_OPS(cpu_s8, YOLOOUTPUT)
UNSUPPORTED_LAYER_OPS(cpu_q8, YOLOOUTPUT)
UNSUPPORTED_LAYER_OPS(cpu_q16, YOLOOUTPUT)
FALLBACK_LAYER_OPS(cl, YOLOOUTPUT, cpu_float)


FALLBACK_TEMPLATE(cpu_s8, cpu_float, cpuq)
FALLBACK_TEMPLATE(cpu_q8, cpu_float, cpuq)
FALLBACK_TEMPLATE(cpu_q16, cpu_float, cpuq)
FALLBACK_TEMPLATE(cl, cpu_float, cl)

