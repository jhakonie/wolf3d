#!/bin/bash
set -e


if [ ! -d "test/build" ]; then
    mkdir test/build
fi


test_xpm_reader() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/we_parse_xpm.c \
	src/we_parse_xpm_hexa.c \
	src/we_parse_xpm_colors.c \
	src/we_parse_xpm_error.c \
	src/we_parse_xpm_pixels.c \
	src/we_parse_until.c \
	src/we_parse_xpm_comment.c \
	src/we_xpm_del.c \
	src/wx_parse_f32.c \
	src/wx_parse_keyword.c \
	src/wx_parse_whitespace.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}

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
	src/wc_p2_lerp.c \
	src/wc_p3_lerp.c \
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
	src/wc_mesh_aabb.c \
	src/wc_mesh_del.c \
	src/wc_mesh_new_from_file.c \
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
	src/wc_u16s_add_back.c \
	src/wc_u16s_del.c \
	src/wc_u16s_new.c \
	src/wc_vertices_add_back.c \
	src/wc_vertices_del.c \
	src/wc_vertices_new.c \
	src/wx_c8s_del.c \
	src/wx_c8s_new_from_file.c \
	src/wx_parse_f32.c \
	src/wx_parse_keyword.c \
	src/wx_parse_whitespace.c \
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
    echo "${test_name}"
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


test_wc_map_new_from_file() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} -I build/libsdl2/include/\
	src/wc_map_new_from_file.c \
	src/wx_buffer_copy.c \
	src/wx_buffer_set.c \
	src/wx_c8s_del.c \
	src/wx_c8s_new_from_file.c \
	src/wx_parse_keyword.c \
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


test_xpm_reader() {
    local test_name=${FUNCNAME}
    rm -f test/build/${test_name}
    gcc -g -Wall -Wextra -l m -o test/build/${test_name} \
	src/wx_parse_hex.c \
	src/wx_parse_xpm_colors.c \
	src/wx_parse_xpm_error.c \
	src/wx_parse_xpm_pixels.c \
	src/wx_parse_xpm_hash_key.c \
	src/wx_parse_until.c \
	src/wx_parse_xpm_comment.c \
	src/wx_xpm_del.c \
	src/wx_parse_f32.c \
	src/wx_parse_keyword.c \
	src/wx_parse_whitespace.c \
	src/wx_buffer_copy.c \
	src/wx_buffer_set.c \
	src/wx_c8s_new_from_file.c \
	src/wx_c8s_del.c \
	-x c test/${test_name}.c.test
    ./test/build/${test_name}
}


declare -a tests
tests[0]="test_2d_raycast"
tests[1]="test_3d_frustum"
tests[2]="test_3d_frustum_aabb"
tests[3]="test_3d_mesh_read"
tests[4]="test_3d_clip_face_plane"
tests[5]="test_3d_pipeline_transform"
tests[6]="test_wc_map_new_from_file"
tests[7]="test_wx_types_h"
tests[8]="test_xpm_reader"


main() {
    echo "================================================================================"
    if [ ${#} -gt 0 ]; then
	for i in "${@}"; do
	    echo "running test: ${i}"
	    ${i}
	    echo "================================================================================"
	done
    else
	for i in "${!tests[@]}"; do
	    echo "running test: ${tests[$i]}"
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
