
global tcc_run, resolve_sym, tcc_set_num_callers
tcc_run:
resolve_sym:
tcc_set_num_callers:
	ret

global dlopen, dlclose
dlopen:
dlclose:
	ret
	
global gettimeofday
gettimeofday:
	ret

global getcwd
getcwd:
	xor eax,eax
	ret
