
#include "nlm_opamp.h"

#include "analog/nld_opamps.h"
#include "devices/nld_system.h"

/*
 *   Generic layout with 4 opamps, VCC on pint 4 and GND on pin 11
 */

NETLIST_START(opamp_layout_4_4_11)
	DIPPINS(      /*   +--------------+   */
		A.OUT,    /*   |1     ++    14|   */ D.OUT,
		A.MINUS,  /*   |2           13|   */ D.MINUS,
		A.PLUS,   /*   |3           12|   */ D.PLUS,
		A.VCC,    /*   |4           11|   */ A.GND,
		B.PLUS,   /*   |5           10|   */ C.PLUS,
		B.MINUS,  /*   |6            9|   */ C.MINUS,
		B.OUT,    /*   |7            8|   */ C.OUT
				  /*   +--------------+   */
	)
	NET_C(A.GND, B.GND, C.GND, D.GND)
	NET_C(A.VCC, B.VCC, C.VCC, D.VCC)
NETLIST_END()

NETLIST_START(MB3614_DIP)
	/* The opamp actually has an FPF of about 500k. This doesn't work here and causes oscillations.
	 * FPF here therefore about half the Solver clock.
	 */
	OPAMP(A, "MB3614")
	OPAMP(B, "MB3614")
	OPAMP(C, "MB3614")
	OPAMP(D, "MB3614")

	INCLUDE(opamp_layout_4_4_11)

NETLIST_END()

NETLIST_START(OPAMP_lib)
	LOCAL_LIB_ENTRY(opamp_layout_4_4_11)

	NET_MODEL(".model MB3614      OPAMP(TYPE=3 VLH=2.0 VLL=0.2 FPF=5 UGF=500k SLEW=0.6M RI=1000k RO=50 DAB=0.002)")
	NET_MODEL(".model MB3614_SLOW OPAMP(TYPE=3 VLH=2.0 VLL=0.2 FPF=5 UGF=11k  SLEW=0.6M RI=1000k RO=50 DAB=0.002)")
	LOCAL_LIB_ENTRY(MB3614_DIP)


NETLIST_END()
