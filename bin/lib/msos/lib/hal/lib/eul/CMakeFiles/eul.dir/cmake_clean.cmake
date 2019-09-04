file(REMOVE_RECURSE
  "libeul.pdb"
  "libeul.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/eul.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
