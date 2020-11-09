#include "build/temp/_test_first.c"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"


void

test_shouldPass(void)

{

   longjmp(Unity.AbortFrame, 1);

}



void

test_shouldFail(void)

{

   UnityFail( (

  ((void *)0)

  ), (UNITY_UINT)(12));

}
