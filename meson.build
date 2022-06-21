project(
    'phosphor-power-control', 'cpp',
    version: '1.0.0',
    meson_version: '>=0.58.0',
    default_options: [
        'warning_level=3',
        'werror=true',
        'cpp_std=c++20',
    ]
)

phosphor_logging_dep = dependency('phosphor-logging')
gpioplus_dep = dependency('gpioplus')

cpp = meson.get_compiler('cpp')
if cpp.has_header_symbol(
        'nlohmann/json.hpp',
        'nlohmann::json::string_t',
        required:false)
    nlohmann_json_dep = declare_dependency()
else
    nlohmann_json_dep = dependency('nlohmann-json')
endif

deps = [
    phosphor_logging_dep,
    nlohmann_json_dep,
    gpioplus_dep,
]

sources = [
    'chassiskill.cpp',
]

executable(
  'chassiskill',
  sources,
  implicit_include_directories: false,
  dependencies: deps,
  install: true,
  install_dir: get_option('libexecdir'))
