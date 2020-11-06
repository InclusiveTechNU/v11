# V11 JS Runtime for A11Y
![Status][14]
[![Apache 2.0 License][15]][10]
[![Travis (.com)][16]][11]
[![Northwestern HCI][17]][12]
[![NSF Grant 1901456][18]][13]


<img src="logo.svg" alt="V11 logo" align="right" width="30%"/>

**Made with :purple_heart: in Evanston, IL at the**
**[Northwestern Inclusive Technology Lab][1]**

V11 is a cross-platform framework for building assistive scripts,
workflows, and plugins. It is built on top of [V8][2] and Node.JS to provide a
lightweight and easy to learn interface for querying and manipulating native
accessibility APIs, while also relieving you of cross-platform nightmares when
building for multiple operating systems.

## Get Started

#### Installing V11

To add V11 to an existing Node.JS project install using:

```shell
yarn add v11
```

#### Building V11 From Source

V11 uses the [Bazel][6] build system for compiling the
project. This allows the project to rely on a single build system for building
all cross-platform components. Once you have installed Bazel you can generate
the V11 developer-mode javascript library by running:

```shell
bazel build //programming/v11/typescript:v11_lib_node_dev
```

The output library can be imported into a Node project using the following
statement:

```javascript
const v11 = require('bazel-bin/programming/v11/typescript/v11.js');
```

#### Examples

V11 is inspired by the DOM to make modifying the accessibility tree easy.
Here's a simple example to mute a track in GarageBand.

```js
const v11 = require('v11');
const gb = v11.system.getApplicationByName("GarageBand");
const mute = gb.getElementsByLabel("Mute")[0];
mute.actions.press();
```

V11 supports more than just performing accessibility actions. In fact, you can
even listen for them too. Here's an example of how to listen for textbox entry
in TextEdit.

```js
const v11 = require('v11');
const notes = v11.system.getApplicationByName("TextEdit");
notes.getElementsByType("textarea")[0].addEventListener('value', () => {
    console.log("hey");
});
```

You can learn about the current stable API
[here][3]. We are continually adding features to improve accessibility
modifications and querying so check back often! You can also see some simple
examples of V11 scripts [here][4]. Additionally, we provide a boilerplate
project to help you get setup [here][5].

Good luck and happy coding!

## Contributing

We welcome contributions of all kinds from filing issues and bug or typo fixes
to large feature implementations. Our team is trying to build the premiere tool
for developing assistive services on all platforms, so we need your help! 

If you have ideas or want to start working on a contribution,
[file an issue][7] and
[submit a pull request][8].

Read more in the CONTRIBUTING.md file.

**This project is supported by [NSF Award 1901456][9]**

[1]: http://inclusive.northwestern.edu/
[2]: https://v8.dev/
[3]: https://northwestern.box.com/s/zvw875xtu7x1iip3alwt7ontelql5ag9
[4]: https://github.com/InclusiveTechNU/v11/tree/master/examples
[5]: https://github.com/inclusivetechnu/v11-boilerplate
[6]: https://bazel.build
[7]: https://github.com/InclusiveTechNU/v11/issues/new
[8]: https://github.com/InclusiveTechNU/v11/compare
[9]: https://www.nsf.gov/awardsearch/showAward?AWD_ID=1901456
[10]: https://github.com/InclusiveTechNU/v11/blob/master/LICENSE
[11]: https://travis-ci.com/InclusiveTechNU/v11
[12]: https://hci.northwestern.edu/
[13]: https://www.nsf.gov/awardsearch/showAward?AWD_ID=1901456
[14]: https://img.shields.io/badge/Version-Experimental-brightgreen.svg
[15]: https://img.shields.io/github/license/inclusivetechnu/v11
[16]: https://img.shields.io/travis/com/InclusiveTechNU/v11
[17]: https://img.shields.io/badge/NU-HCI-blueviolet
[18]: https://img.shields.io/badge/NSF-1901456-informational
