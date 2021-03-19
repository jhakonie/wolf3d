#!/bin/bash
set -eu


if [ ! -d "test/build" ]; then
    mkdir -f test/build
fi


test_2d_raycast() {
    local test_name=test_2d_raycast
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_3d_mesh_read() {
    local test_name=test_3d_mesh_read
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wc_darray_add_back.c \
	src/wc_darray_add_back_be.c \
	src/wc_darray_del.c \
	src/wc_darray_new.c \
	src/wc_darray_new_file.c \
	src/wc_mesh_new.c \
	src/wc_parse_comment.c \
	src/wc_parse_face.c \
	src/wc_parse_f32.c \
	src/wc_parse_keyword.c \
	src/wc_parse_material_name.c \
	src/wc_parse_material_filename.c \
	src/wc_parse_normal.c \
	src/wc_parse_object_name.c \
	src/wc_parse_smoothing.c \
	src/wc_parse_position.c \
	src/wc_parse_u16.c \
	src/wc_parse_u32.c \
	src/wc_parse_uvcoord.c \
	src/wc_parse_whitespace.c \
	src/wx_buffer_copy.c \
	src/wx_buffer_set.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_3d_pipeline_transform() {
    local test_name=test_3d_pipeline_transform
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wx_buffer_set.c \
	src/wx_m44_mul_m44.c \
	src/wx_m44_mul_p3.c \
	src/wx_m44_mul_p4.c \
	src/wx_m44_new_inverse_q4_p3.c \
	src/wx_m44_new_perspective.c \
	src/wx_m44_new_q4_p3.c \
	src/wx_q4_new_v3_f32.c \
	src/wx_to_radians.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_wx_types_h() {
    local test_name=test_wx_types_h
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wx_buffer_set.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


declare -a tests
tests[0]="test_2d_raycast"
tests[1]="test_3d_mesh_read"
tests[2]="test_3d_pipeline_transform"
tests[3]="test_wx_types_h"

main() {
    echo "================================================================================"
    if [ ${#} -gt 0 ]; then
	for i in "${@}"; do
	    ${i}
	    echo "================================================================================"
	done
    else
	for i in "${!tests[@]}"; do
	    ${tests[$i]}
	    echo "================================================================================"
	done
    fi
}
main "${@}"
