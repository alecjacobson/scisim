include( CMakeSourceFiles.txt )

add_executable( rigidbody3d_cli ${Headers} ${Sources} )
if( ENABLE_IWYU )
  set_property( TARGET rigidbody3d_cli PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path} )
endif()

if( CMAKE_Fortran_COMPILER )
  set_source_files_properties( rigidbody3d_cli.cpp PROPERTIES COMPILE_DEFINITIONS FORTRAN_FOUND )
endif()

target_link_libraries( rigidbody3d_cli rigidbody3dutils rigidbody3d )

execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/assets/rigidbody3d ${CMAKE_CURRENT_BINARY_DIR}/assets )
execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/post_processing ${CMAKE_CURRENT_BINARY_DIR}/post_processing )

# Serialization and resume tests
if( USE_HDF5 AND H5DIFF_FOUND )
  add_test( rb3d_serialization_00 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/card_house.xml 1 0999 0431 )
  add_test( rb3d_serialization_01 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/friction_collide_in_portal.xml 5 499 147 )
  add_test( rb3d_serialization_02_a assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/ball_rolling_in_container.xml 2.35 2299 1152 )
  add_test( rb3d_serialization_02_b assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/balls_rolling_in_container.xml 2.35 2299 1152 )
  add_test( rb3d_serialization_03 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/one_dim_test_0.xml 2.0 20 03 )
  add_test( rb3d_serialization_04 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/one_dim_test_1.xml 2.0 200 033 )
  add_test( rb3d_serialization_05 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/one_dim_test_2.xml 2.0 200 033 )
  add_test( rb3d_serialization_06 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/one_dim_test_3.xml 2.0 200 033 )
  add_test( rb3d_serialization_07 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/box_box_test_0.xml 2.0 200 033 )
  add_test( rb3d_serialization_08 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/box_box_test_1.xml 2.0 200 033 )
  add_test( rb3d_serialization_09 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/box_box_test_2.xml 2.0 200 033 )
  add_test( rb3d_serialization_10 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/two_dragon_drop.xml 1.0 50 27 50 )
  add_test( rb3d_serialization_20 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/sphere_in_off_center_cylinder.xml 4.0 40 23 10 )
  add_test( rb3d_serialization_21 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/sphere_in_off_center_cylinder_sym_eul.xml 4.0 40 14 10 )
  # Stabilized map tests
  add_test( rb3d_serialization_11 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/drift_safe_ball_on_plane.xml 2.0 20 05 10 )
  add_test( rb3d_serialization_12 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/drift_safe_balls_on_planes_00.xml 2.5 25 08 10 )
  add_test( rb3d_serialization_13 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/drift_safe_balls_on_planes_01.xml 3.0 300 080 100 )
  add_test( rb3d_serialization_14 assets/shell_scripts/execute_serialization_test.sh assets/tests_serialization/drift_safe_two_dragon_drop.xml 1.0 50 27 50 )
  # Symplectic Euler tests
  add_test( rb3d_serialization_15 assets/shell_scripts/execute_serialization_test.sh assets/tests_symplectic_euler/sphere_falling_on_fixed_spheres.xml 1.0 100 061 100 )
  add_test( rb3d_serialization_16 assets/shell_scripts/execute_serialization_test.sh assets/tests_symplectic_euler/sphere_falling_on_plane.xml 1.0 100 032 100 )
  add_test( rb3d_serialization_17 assets/shell_scripts/execute_serialization_test.sh assets/tests_symplectic_euler/spheres_rolling_on_planes.xml 2.0 200 083 100 )
  add_test( rb3d_serialization_18 assets/shell_scripts/execute_serialization_test.sh assets/tests_symplectic_euler/spheres_in_planes_0.xml 2.5 125 051 50 )
  add_test( rb3d_serialization_19 assets/shell_scripts/execute_serialization_test.sh assets/tests_symplectic_euler/spheres_in_planes_1.xml 7.0 70 37 10 )
else()
  message( STATUS "Skipping RigidBody3D tests that require HDF5 (USE_HDF5 is disabled or h5diff not found)." )
endif()

# Serialization and resume tests
if( USE_HDF5 AND H5DIFF_FOUND AND USE_PYTHON )
  add_test( rb3d_serialization_scripting_00 assets/shell_scripts/execute_serialization_test.sh assets/tests_python_serialization/different_friction.xml 2 199 051 )
  add_test( rb3d_serialization_scripting_01 assets/shell_scripts/execute_serialization_test.sh assets/tests_python_serialization/oscillating_plane.xml 11 1099 0512 )
  add_test( rb3d_serialization_scripting_02 assets/shell_scripts/execute_serialization_test.sh assets/tests_python_serialization/sphere_in_cylinder.xml 10 0999 0654 )
  add_test( rb3d_serialization_scripting_03 assets/shell_scripts/execute_serialization_test.sh assets/tests_python_serialization/translating_plane.xml 20 200 137 10 )
  add_test( rb3d_serialization_scripting_04 assets/shell_scripts/execute_serialization_test.sh assets/tests_python_serialization/different_restitution.xml 3.0 300 172 100 )
else()
  message( STATUS "Skipping RigidBody3D tests that require Python and HDF5 (USE_PYTHON or USE_HDF5 is disabled or h5diff not found)." )
endif()

# Serialization tests for simulations that use Ipopt
if( USE_HDF5 AND H5DIFF_FOUND AND USE_IPOPT )
  add_test( rb3d_ipopt_serialization_0 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/one_dim_test_0.xml 2.0 20 03 )
  add_test( rb3d_ipopt_serialization_1 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/one_dim_test_1.xml 2.0 200 033 )
  add_test( rb3d_ipopt_serialization_2 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/one_dim_test_2.xml 2.0 200 033 )
  add_test( rb3d_ipopt_serialization_3 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/one_dim_test_3.xml 2.0 200 033 )
  add_test( rb3d_ipopt_serialization_4 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/box_box_test_0.xml 2.0 200 033 )
  add_test( rb3d_ipopt_serialization_5 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/box_box_test_1.xml 2.0 200 033 )
  add_test( rb3d_ipopt_serialization_6 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/box_box_test_2.xml 2.0 200 033 )
  add_test( rb3d_ipopt_serialization_7 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/kinematic_object_test.xml 3.0 30 13 )
  add_test( rb3d_ipopt_serialization_8 assets/shell_scripts/execute_serialization_test.sh assets/tests_ipopt_serialization/sphere_sphere_smooth_friction.xml 2.0 200 013 )
else()
  message( STATUS "Skipping RigidBody3D tests that require Ipopt and HDF5 (USE_IPOPT or USE_HDF5 is disabled or h5diff not found)." )
endif()
