# How to Contribute

We welcome contributions of all kinds from filing issues and bug or typo fixes to large feature implementations. 
Our team is trying to build the premiere tool for developing assistive services on all platforms, so we need your help! 

If you have ideas or want to start working on a contribution, [file an issue](https://github.com/InclusiveTechNU/v11/issues/new) and 
[submit a pull request](https://github.com/InclusiveTechNU/v11/compare). After it has been
reviewed and approved by a [commiter](https://github.com/InclusiveTechNU/v11/blob/master/CODEOWNERS), your changes will slide 
right into `master`. When you file your 10th commit, you will automatically be considered for 
committer status and will be able to work right in the repository with the other members of the V11 team.

## Code reviews

All submissions, including submissions by project members, require review. We
use GitHub pull requests for this purpose. Consult
[GitHub Help](https://help.github.com/articles/about-pull-requests/) for more
information on using pull requests.

## License

Make sure to check out the LICENSE file for the details on the Apache 2.0 License
that we use for the V11 project.

## Community Guidelines

Check out the CODE_OF_CONDUCT.md file for details on our code of conduct.

## Source Code Headers

Every file containing source code must include copyright and license
information. This includes any JS/CSS files that you might be serving out to
browsers. (This is to help well-intentioned people avoid accidental copying that
doesn't comply with the license.)

Apache header:

    Copyright 2020 Northwestern Inclusive Technology Lab

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        https://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

## Code Style Guidelines

All code must pass our linter which follows the Google [C++ Code Style Guidelines](https://google.github.io/styleguide/cppguide.html).
To test contributions against our suite of linting tests run
```shell
./utils/lint/lint
```

For questions, comments, and concerns, please reach out to Tommy McHugh at [mchugh@u.northwestern.edu](mailto:mchugh@u.northwestern.edu)
