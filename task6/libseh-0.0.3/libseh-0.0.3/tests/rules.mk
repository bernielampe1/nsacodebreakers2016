TESTS = div_zero$(EXE_EXT) null_pointer$(EXE_EXT) null_pointer_cxx$(EXE_EXT) finally$(EXE_EXT) noexcept$(EXE_EXT)
OBJS = div_zero$(OBJ_EXT) null_pointer$(OBJ_EXT) null_pointer_cxx$(OBJ_EXT) finally$(OBJ_EXT) noexcept$(OBJ_EXT)

div_zero$(EXE_EXT): div_zero$(OBJ_EXT)
null_pointer$(EXE_EXT): null_pointer$(OBJ_EXT)
null_pointer_cxx$(EXE_EXT): null_pointer_cxx$(OBJ_EXT)
finally$(EXE_EXT): finally$(OBJ_EXT)
noexcept$(EXE_EXT): noexcept$(OBJ_EXT)

