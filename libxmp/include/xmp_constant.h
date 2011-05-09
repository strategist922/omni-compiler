/*
 * $TSUKUBA_Release: $
 * $TSUKUBA_Copyright:
 *  $
 */

#ifndef _XMP_CONSTANT
#define _XMP_CONSTANT

#define _XMP_N_INT_TRUE				1
#define _XMP_N_INT_FALSE			0
#define _XMP_N_MAX_DIM				7

// constants for mpi tag
#define _XMP_N_MPI_TAG_GMOVE			10
#define _XMP_N_MPI_TAG_REFLECT_LO		11
#define _XMP_N_MPI_TAG_REFLECT_HI		12

// constants used in runtime functions
#define _XMP_N_INVALID_RANK			-1
#define _XMP_N_NO_ALIGNED_TEMPLATE		-1
#define _XMP_N_NO_ONTO_NODES			-1
#define _XMP_N_DEFAULT_ROOT_RANK		0

// defined in exc.xcalablemp.XMPtemplate
#define _XMP_N_DIST_DUPLICATION			100
#define _XMP_N_DIST_BLOCK			101
#define _XMP_N_DIST_CYCLIC			102

// FIXME defined in exc.xcalablemp.XMP???
#define _XMP_N_ALIGN_NOT_ALIGNED		200
#define _XMP_N_ALIGN_DUPLICATION		201
#define _XMP_N_ALIGN_BLOCK			202
#define _XMP_N_ALIGN_CYCLIC			203

// defined in exc.xcalablemp.XMPcollective
#define _XMP_N_REDUCE_SUM			300
#define _XMP_N_REDUCE_PROD			301
#define _XMP_N_REDUCE_BAND			302
#define _XMP_N_REDUCE_LAND			303
#define _XMP_N_REDUCE_BOR			304
#define _XMP_N_REDUCE_LOR			305
#define _XMP_N_REDUCE_BXOR			306
#define _XMP_N_REDUCE_LXOR			307
#define _XMP_N_REDUCE_MAX			308
#define _XMP_N_REDUCE_MIN			309
#define _XMP_N_REDUCE_FIRSTMAX			310
#define _XMP_N_REDUCE_FIRSTMIN			311
#define _XMP_N_REDUCE_LASTMAX			312
#define _XMP_N_REDUCE_LASTMIN			313

// defined in exc.xcalablemp.XMPshadow
#define _XMP_N_SHADOW_NONE			400
#define _XMP_N_SHADOW_NORMAL			401
#define _XMP_N_SHADOW_FULL			402

// defined in exc.object.BasicType + 500
#define _XMP_N_TYPE_BOOL			502
#define _XMP_N_TYPE_CHAR			503
#define _XMP_N_TYPE_UNSIGNED_CHAR		504
#define _XMP_N_TYPE_SHORT			505
#define _XMP_N_TYPE_UNSIGNED_SHORT		506
#define _XMP_N_TYPE_INT				507
#define _XMP_N_TYPE_UNSIGNED_INT		508
#define _XMP_N_TYPE_LONG			509
#define _XMP_N_TYPE_UNSIGNED_LONG		510
#define _XMP_N_TYPE_LONGLONG			511
#define _XMP_N_TYPE_UNSIGNED_LONGLONG		512
#define _XMP_N_TYPE_FLOAT			513
#define _XMP_N_TYPE_DOUBLE			514
#define _XMP_N_TYPE_LONG_DOUBLE			515
#define _XMP_N_TYPE_FLOAT_IMAGINARY		516
#define _XMP_N_TYPE_DOUBLE_IMAGINARY		517
#define _XMP_N_TYPE_LONG_DOUBLE_IMAGINARY	518
#define _XMP_N_TYPE_FLOAT_COMPLEX		519
#define _XMP_N_TYPE_DOUBLE_COMPLEX		520
#define _XMP_N_TYPE_LONG_DOUBLE_COMPLEX		521
#define _XMP_N_TYPE_NONBASIC			599

// defined in exc.xcalablemp.XMPgpuData
#define _XMP_N_GPUSYNC_IN			600
#define _XMP_N_GPUSYNC_OUT			601

#endif // _XMP_CONSTANT
