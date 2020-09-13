{
  "targets": [
    {
      "target_name": "{{TARGET_NAME}}",
      "include_dirs": {{INCLUDE_DIRS}},
      "libraries": {{DEPENDENCIES}},
      "sources": {{SOURCES}},
      "cflags": {{CFLAGS}},
      'link_settings': {
        'libraries': {{MACOS_SDKS}},
      },
    },
  ]
}