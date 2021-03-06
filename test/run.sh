#!/bin/bash
set -eu


if [ ! -d "test/build" ]; then
    mkdir -f test/build
fi


test_name=test_3d_pipeline_transform
rm -f test/build/${test_name}
gcc -Wall -Wextra -l m -o test/build/${test_name}\
    src/wx_buffer_set.c\
    src/wx_m44_mul_m44.c\
    src/wx_m44_mul_p3.c\
    src/wx_m44_mul_p4.c\
    src/wx_m44_new_inverse_q4_p3.c\
    src/wx_m44_new_perspective.c\
    src/wx_m44_new_q4_p3.c\
    src/wx_q4_new_v3_f32.c\
    src/wx_to_radians.c\
    -x c test/${test_name}.c.test
./test/build/${test_name}
