#include "HoldMethod.h"

void HoldMethod::Pay(PayCheck& pc) { pc.SetField("Disposition", "Hold"); }