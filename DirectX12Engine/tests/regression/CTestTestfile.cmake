# CMake generated Testfile for 
# Source directory: C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression
# Build directory: C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/tests/regression
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(regression_delayed_reg "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/bin/slang.exe" "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/delayed_reg.v")
  set_tests_properties(regression_delayed_reg PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;1;add_test;C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(regression_delayed_reg "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/bin/slang.exe" "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/delayed_reg.v")
  set_tests_properties(regression_delayed_reg PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;1;add_test;C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(regression_delayed_reg "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/bin/slang.exe" "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/delayed_reg.v")
  set_tests_properties(regression_delayed_reg PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;1;add_test;C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(regression_delayed_reg "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/bin/slang.exe" "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/delayed_reg.v")
  set_tests_properties(regression_delayed_reg PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;1;add_test;C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;0;")
else()
  add_test(regression_delayed_reg NOT_AVAILABLE)
endif()
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(regression_wire_module "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/bin/slang.exe" "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/wire_module.v")
  set_tests_properties(regression_wire_module PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;2;add_test;C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(regression_wire_module "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/bin/slang.exe" "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/wire_module.v")
  set_tests_properties(regression_wire_module PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;2;add_test;C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(regression_wire_module "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/bin/slang.exe" "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/wire_module.v")
  set_tests_properties(regression_wire_module PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;2;add_test;C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(regression_wire_module "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/bin/slang.exe" "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/wire_module.v")
  set_tests_properties(regression_wire_module PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;2;add_test;C:/Users/hatte/SELFGAMEENGINE/DirectX12Engine/DirectX12Engine/slang/tests/regression/CMakeLists.txt;0;")
else()
  add_test(regression_wire_module NOT_AVAILABLE)
endif()
