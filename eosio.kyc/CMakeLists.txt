add_contract(eosio.kyc eosio.kyc ${CMAKE_CURRENT_SOURCE_DIR}/src/eosio.kyc.cpp)

target_include_directories(eosio.kyc
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(eosio.kyc
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/eosio.kyc.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/eosio.kyc.contracts.md @ONLY )

target_compile_options( eosio.kyc PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
