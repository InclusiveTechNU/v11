{
  "targets": [
    {
      "target_name": "larkin",
      "sources": [
        # Main Binding File
        "binding.cc",

        # Interactions
        "interaction.cc",
        "interaction.h"
      ],
      "libraries": [
        '-L/Users/tommymchugh/Developer/v11/bazel-bin/larkin/', '-llarkin'
      ]
    }
  ]
}