base64_simd_system_headers = [

]
base64_simd_local_headers = [
  'base64_simd/include/libbase64.h',
  'base64_simd/lib/codecs.h',
  'base64_simd/lib/env.h',
  'base64_simd/lib/tables/table_dec_32bit.h',
  'base64_simd/lib/tables/table_enc_12bit.h',
  'base64_simd/lib/tables/tables.h',
  'base64_simd/test/codec_supported.h',
  'base64_simd/test/moby_dick.h',
]
base64_simd_srcs = [
  '../../../submodules/base64_simd/bin/base64.c',
  '../../../submodules/base64_simd/lib/arch/avx/codec.c',
  '../../../submodules/base64_simd/lib/arch/avx/enc_loop_asm.c',
  '../../../submodules/base64_simd/lib/arch/avx2/codec.c',
  '../../../submodules/base64_simd/lib/arch/avx2/dec_loop.c',
  '../../../submodules/base64_simd/lib/arch/avx2/dec_reshuffle.c',
  '../../../submodules/base64_simd/lib/arch/avx2/enc_loop.c',
  '../../../submodules/base64_simd/lib/arch/avx2/enc_loop_asm.c',
  '../../../submodules/base64_simd/lib/arch/avx2/enc_reshuffle.c',
  '../../../submodules/base64_simd/lib/arch/avx2/enc_translate.c',
  '../../../submodules/base64_simd/lib/arch/avx512/codec.c',
  '../../../submodules/base64_simd/lib/arch/avx512/enc_loop.c',
  '../../../submodules/base64_simd/lib/arch/avx512/enc_reshuffle_translate.c',
  '../../../submodules/base64_simd/lib/arch/generic/32/dec_loop.c',
  '../../../submodules/base64_simd/lib/arch/generic/32/enc_loop.c',
  '../../../submodules/base64_simd/lib/arch/generic/64/enc_loop.c',
  '../../../submodules/base64_simd/lib/arch/generic/codec.c',
  '../../../submodules/base64_simd/lib/arch/generic/dec_head.c',
  '../../../submodules/base64_simd/lib/arch/generic/dec_tail.c',
  '../../../submodules/base64_simd/lib/arch/generic/enc_head.c',
  '../../../submodules/base64_simd/lib/arch/generic/enc_tail.c',
  '../../../submodules/base64_simd/lib/arch/neon32/codec.c',
  '../../../submodules/base64_simd/lib/arch/neon32/dec_loop.c',
  '../../../submodules/base64_simd/lib/arch/neon32/enc_loop.c',
  '../../../submodules/base64_simd/lib/arch/neon32/enc_reshuffle.c',
  '../../../submodules/base64_simd/lib/arch/neon32/enc_translate.c',
  '../../../submodules/base64_simd/lib/arch/neon64/codec.c',
  '../../../submodules/base64_simd/lib/arch/neon64/dec_loop.c',
  '../../../submodules/base64_simd/lib/arch/neon64/enc_loop.c',
  '../../../submodules/base64_simd/lib/arch/neon64/enc_loop_asm.c',
  '../../../submodules/base64_simd/lib/arch/neon64/enc_reshuffle.c',
  '../../../submodules/base64_simd/lib/arch/sse41/codec.c',
  '../../../submodules/base64_simd/lib/arch/sse42/codec.c',
  '../../../submodules/base64_simd/lib/arch/ssse3/codec.c',
  '../../../submodules/base64_simd/lib/arch/ssse3/dec_loop.c',
  '../../../submodules/base64_simd/lib/arch/ssse3/dec_reshuffle.c',
  '../../../submodules/base64_simd/lib/arch/ssse3/enc_loop.c',
  '../../../submodules/base64_simd/lib/arch/ssse3/enc_loop_asm.c',
  '../../../submodules/base64_simd/lib/arch/ssse3/enc_reshuffle.c',
  '../../../submodules/base64_simd/lib/arch/ssse3/enc_translate.c',
  '../../../submodules/base64_simd/lib/codec_choose.c',
  '../../../submodules/base64_simd/lib/lib.c',
  '../../../submodules/base64_simd/lib/lib_openmp.c',
  '../../../submodules/base64_simd/lib/tables/table_generator.c',
  '../../../submodules/base64_simd/lib/tables/tables.c',
]

base64_simd_dirs = [
  '../../../submodules/base64_simd',
  inc,
]

base64_simd_c_args = [
]

base64_simd_deps = [

]

if base64_simd_srcs.length() > 0
  base64_simd_lib = library('base64_simd',
    files(base64_simd_srcs),
    install: false,
    dependencies: base64_simd_deps,
    include_directories: base64_simd_dirs,
    c_args: base64_simd_c_args,
  )
  base64_simd_links = [base64_simd_lib]
else
  base64_simd_links = []
endif

base64_simd_dep = declare_dependency(
  include_directories: base64_simd_dirs,
  link_with: base64_simd_links,
)
