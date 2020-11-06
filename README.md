# V11 JS Runtime for A11Y
[![Apache 2.0 License](https://img.shields.io/github/license/inclusivetechnu/v11)](https://github.com/InclusiveTechNU/v11/blob/master/LICENSE)
[![Travis (.com)](https://img.shields.io/travis/com/InclusiveTechNU/v11)](https://travis-ci.com/InclusiveTechNU/v11)
[![Northwestern HCI](https://img.shields.io/badge/NU-HCI-blueviolet)](https://hci.northwestern.edu/)
[![NSF Grant 1901456](https://img.shields.io/badge/NSF-1901456-informational)](https://www.nsf.gov/awardsearch/showAward?AWD_ID=1901456)


<img src="logo.svg" alt="V11 logo" align="right" width="30%"/>

**Made with :purple_heart: in Evanston, IL at the [Northwestern Inclusive Technology Lab](http://inclusive.northwestern.edu/)**

V11 is a JavaScript library and code editor for building accessibility plugins, workflows, and applications. It is built on top of [V8](https://v8.dev/) and Node.JS to provide a lightweight and easy to learn interface for manipulating applications and accessibility APIs using the features you love from JavaScript, while also relieving you of cross-platform nightmares.

*This is currently a developer preview of V11. We are planning a full launch in Fall 2020.*

**Example**

V11 is inspired by the DOM to make modifying the accessibility tree easy. Here's a simple example to mute a track in GarageBand.

```js
const v11 = require('v11');
const gb = v11.system.getApplicationByName("GarageBand");
const mute = gb.getElementsByLabel("Mute")[0];
mute.actions.press();
```

V11 supports more than just performing accessibility actions. In fact, you can even listen for them too. Here's an example of how to listen for textbox entry in TextEdit.

```js
const v11 = require('v11');
const notes = v11.system.getApplicationByName("TextEdit");
notes.getElementsByType("textarea")[0].addEventListener('value', () => {
    console.log("hey");
});
```

You can learn about the current stable API [here](https://northwestern.box.com/s/zvw875xtu7x1iip3alwt7ontelql5ag9). We are continually adding features to improve accessibility modification and querying so check back often! You can also see some simple examples of V11 scripts [here](https://github.com/InclusiveTechNU/v11/tree/master/examples).

**Installing V11**

To add V11 to an existing Node.JS project install using

```shell
yarn add v11
```

Good luck and happy coding!

**Building V11**

While we are currently transitioning to the Bazel build system, most of the project relies on Yarn for building. These instructions will build V11 from source.

```shell
yarn install
yarn build
```

Get started building a V11 application [here](https://github.com/inclusivetechnu/v11-boilerplate).

## Contributing

We welcome contributions of all kinds from filing issues and bug or typo fixes to large feature implementations. 
Our team is trying to build the premiere tool for developing assistive services on all platforms, so we need your help! 

If you have ideas or want to start working on a contribution, [file an issue](https://github.com/InclusiveTechNU/v11/issues/new) and [submit a pull request](https://github.com/InclusiveTechNU/v11/compare).

Read more in the CONTRIBUTING.md file.

**This project is supported by [NSF Award 1901456](https://www.nsf.gov/awardsearch/showAward?AWD_ID=1901456)**
