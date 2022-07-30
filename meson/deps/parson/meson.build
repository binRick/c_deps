#parson_dep = dependency('parson', fallback:['parson', 'shared_parson_dep'])
#parson_dep = dependency('parson',fallback:['parson', 'parson_shared_dep'])
parson_dep = dependency('parson', method: 'pkg-config', required: true, fallback:['parson','parson_shared_dep'])
#parson_dep = dependency('parson', method: 'pkg-config', required: true, fallback: ['parson', 'parson_dep'])

#parson = cc.find_library('parson', required: true)

