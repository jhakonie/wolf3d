#!/bin/bash
set -e


if [ ! -d "test/build" ]; then
    mkdir test/build
fi


test_2d_raycast() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_3d_clip_face_plane()
{
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wc_draw_add_visible.c \
	src/wc_draw_clip.c \
	src/wx_plane_line_test.c \
	src/wx_plane_signed_distance_p3.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_3d_frustum() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wx_buffer_set.c \
	src/wx_frustum_new.c \
	src/wx_m44_new_perspective.c \
	src/wx_plane_new.c \
	src/wx_plane_signed_distance_p3.c \
	src/wx_to_radians.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_3d_frustum_aabb() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wx_buffer_set.c \
	src/wx_f32_max.c \
	src/wx_f32_min.c \
	src/wx_frustum_aabb_test.c \
	src/wx_frustum_new.c \
	src/wx_m44_mul_m44.c \
	src/wx_m44_mul_p3.c \
	src/wx_m44_new_inverse_q4_p3.c \
	src/wx_m44_new_perspective.c \
	src/wx_m44_new_q4_p3.c \
	src/wx_obb_new.c \
	src/wx_plane_new.c \
	src/wx_plane_signed_distance_n3.c \
	src/wx_plane_signed_distance_p3.c \
	src/wx_q4_new_v3_f32.c \
	src/wx_to_radians.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_3d_mesh_read() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wx_c8s_del.c \
	src/wx_c8s_new_from_file.c \
	src/wc_mesh_del.c \
	src/wc_mesh_new.c \
	src/wc_n3s_add_back.c \
	src/wc_n3s_del.c \
	src/wc_n3s_new.c \
	src/wc_obj_vertices_add_back.c \
	src/wc_obj_vertices_del.c \
	src/wc_obj_vertices_new.c \
	src/wc_p2s_add_back.c \
	src/wc_p2s_del.c \
	src/wc_p2s_new.c \
	src/wc_p3s_add_back.c \
	src/wc_p3s_del.c \
	src/wc_p3s_new.c \
	src/wx_parse_f32.c \
	src/wx_parse_keyword.c \
	src/wc_parse_obj.c \
	src/wc_parse_obj_comment.c \
	src/wc_parse_obj_context_del.c \
	src/wc_parse_obj_context_new.c \
	src/wc_parse_obj_face.c \
	src/wc_parse_obj_material_filename.c \
	src/wc_parse_obj_material_name.c \
	src/wc_parse_obj_normal.c \
	src/wc_parse_obj_object_name.c \
	src/wc_parse_obj_position.c \
	src/wc_parse_obj_smoothing.c \
	src/wc_parse_obj_uv.c \
	src/wc_parse_u16.c \
	src/wx_parse_whitespace.c \
	src/wc_vertices_add_back.c \
	src/wc_vertices_del.c \
	src/wc_vertices_new.c \
	src/wc_u16s_add_back.c \
	src/wc_u16s_del.c \
	src/wc_u16s_new.c \
	src/wx_buffer_copy.c \
	src/wx_buffer_set.c \
	src/wx_f32_max.c \
	src/wx_f32_min.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_3d_pipeline_transform() {
    local test_name=${FUNCNAME}
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


test_3d_screen_area() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_wx_types_h() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wx_buffer_set.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


declare -a tests
tests[0]="test_2d_raycast"
tests[1]="test_3d_frustum"
tests[2]="test_3d_frustum_aabb"
tests[3]="test_3d_mesh_read"
tests[4]="test_3d_pipeline_transform"
tests[4]="test_3d_clip_face_plane"
tests[5]="test_wx_types_h"


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


if [ ${#} -gt 0 ]; then
    main "${@}"
else
    main
fi
