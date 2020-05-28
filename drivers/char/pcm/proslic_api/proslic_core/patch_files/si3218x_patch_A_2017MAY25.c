/*
** Patch:  si3218x_patch_A_2017MAY25.c
** Copyright 2017, Silicon Labs
**
** Generated from si3218x_patch_A_2017MAY25.dsp_prom
** on 05-25-2017 at 15:1:37
** Patch ID = 0x05252017L
**
** This file contains proprietary information.
** No dissemination allowed without prior written permission from
** Silicon Laboratories, Inc.
*/
#include "si_voice_datatypes.h"
#include "si3218x.h"

static const uInt32 patchData [] = {
141029L,
540867L,
141029L,
543427L,
141029L,
553667L,
141029L,
562883L,
141029L,
567491L,
141029L,
569539L,
141029L,
580803L,
141029L,
586435L,
141029L,
593091L,
141029L,
598211L,
141029L,
603843L,
141029L,
604355L,
141029L,
604867L,
141029L,
605379L,
141029L,
605891L,
141029L,
606403L,
736L,
492224L,
452200L,
141029L,
491712L,
558181L,
410018L,
539765L,
142565L,
551619L,
355746L,
539765L,
142560L,
548547L,
767493L,
356258L,
407477L,
142561L,
551619L,
767493L,
539749L,
743525L,
119426L,
141029L,
925377L,
387589L,
558181L,
388514L,
387701L,
142565L,
561347L,
524290L,
144096L,
559811L,
524292L,
141029L,
560835L,
524290L,
437360L,
671749L,
437349L,
141029L,
21186L,
560741L,
524290L,
143072L,
565955L,
141029L,
122050L,
694789L,
141029L,
789186L,
408165L,
408645L,
141029L,
950976L,
524291L,
144101L,
571587L,
199685L,
666853L,
574659L,
431717L,
197189L,
136805L,
198725L,
408677L,
262242L,
524291L,
144101L,
577731L,
408581L,
666853L,
873664L,
136805L,
407621L,
141029L,
873664L,
9733L,
136805L,
116130L,
524304L,
660069L,
440424L,
9827L,
660066L,
524315L,
141029L,
674496L,
694789L,
828517L,
119426L,
267414L,
829441L,
828933L,
694789L,
118405L,
788805L,
725829L,
119424L,
141029L,
230594L,
492645L,
252002L,
524295L,
517220L,
144101L,
596675L,
517733L,
827461L,
141029L,
745664L,
466437L,
558181L,
410018L,
519797L,
142565L,
601795L,
385637L,
466597L,
524289L,
141029L,
27330L,
524293L,
524293L,
524293L,
524293L,
524293L,
524293L,
0L
};

static const uInt16 patchEntries [] = {
951,
3854,
4136,
4333,
1856,
1695,
1316,
4545,
1455,
4148,
0,
0,
0,
0,
0,
0
};

static const uInt16 patchSupportAddr [] = {
800,
694,
695,
795,
914,
758,
757,
798,
797,
796,
226,
1011,
1010,
0
};

static const uInt32 patchSupportData [] = {
0x200000L,
0x80000L,
0x200000L,
0x180000L,
0x07FCFDDAL,
0x400000L,
0x0L,
0x123400L,
0x123400L,
0x123400L,
0x35D540L,
0x3F00000L,
0x100000L,
0x0L
};

#ifdef SIVOICE_MULTI_BOM_SUPPORT
const proslicPatch si3218xPatchRevALCQC = {
#else
const proslicPatch RevAPatch = {
#endif
    patchData,
    patchEntries,
    0x05252017L,
    patchSupportAddr,
    patchSupportData
};