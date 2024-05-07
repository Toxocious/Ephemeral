# Contributing To Ephemeral
Thanks for your interest in contributing to Ephemeral! :tada: We love getting [pull requests](https://www.quora.com/GitHub-What-is-a-pull-request) for bugfixes and contributions of our community to keep Ephemeral growing.

We want to keep it as easy as possible to contribute changes. These guidelines are intended to help smooth that process and allow us to review and approve your changes quickly and easily. Improvements are always welcome!

Feel free to [open an issue](https://github.com/Toxocious/Ephemeral/issues/new) or [submit a new pull request](https://github.com/Toxocious/Ephemeral/compare). And finally, these are just guidelines, not rules, so use your best judgement when necessary.

If you're looking for inspiration for something to do, feel free to check out any open issues. We try to tag bug fixes or feature suggestions issues with [#good-first-issue](https://github.com/Toxocious/Ephemeral/issues?q=is%3Aissue+is%3Aopen+label%3A%22good+first+issue%22) when applicable, so check those ones out first if you're not yet accustomed to the code-base.

We only ask that you keep your code clean and easily readable.

We try to respond to pull requests within a few days, but feel free to bump yours or ping us over Discord if it seems like we forget about it. Sometimes we did, and sometimes there might be a miscommunication in terms of who is waiting for what.



## Reporting Bugs
Bugs should be reported on our [GitHub Issue Tracker](https://github.com/Toxocious/Ephemeral/issues/new) and should be correctly labeled as a `bug`.



## Requesting New Features
Feature requests should also be sent to our [GitHub Issue Tracker](https://github.com/Toxocious/Ephemeral/issues/new) and should be correctly labeled as a `feature`, with additional labels if necessary.

- Explain the problem that you're having, and anything you've tried to solve it using the currently available features.
- Explain how this new feature will help.
- If possible, provide an example, like a code snippet, showing what your new feature might look like in use.



## Contributing a Fix or Feature
You've created a new fix or feature for Ephemeral. Awesome!

1. If you haven't already, create a fork of the Ephemeral repository.
2. Create a topic branch, and make all of your changes on that branch.
3. Submit a pull request, providing any essential details and information regarding your code and the issue/feature that you aim to resolve/implement.
4. Give me a moment. Ephemeral is maintained by a single person who does this on their limited free time, so it may take a bit to review your request. Bug fixes should be merged in directly, while features usually require Jess's approval.

If you're not sure what any of that means, check out Thinkful's [GitHub Pull Request Tutorial](https://github.com/Thinkful/guide-github-pull-request/blob/master/index.md) for a complete walkthrough of the process.



## Pull Requests
We expect any pull requests to be made from a new branch, where the branch name is a brief descriptor of what to expect from the pull request.

Here's some steps on creating your own branch.

1. Fork the Project
2. Create your Feature Branch (``git checkout -b type-branch_name``)
3. Commit your Changes (``git commit -m 'commit description'``)
4. Push to the Branch (``git push origin type-branch_name``)
5. Open a Pull Request

### Writing a Good Pull Request
Some tips on writing a good pull request are as follows:

- Stay focused on a single fix or feature. If you submit multiple changes in a single request, we may like some but spot issues with others. When that happens, we have to reject the whole thing. If you submit each change in its own request it is easier for us to review and approve.
- Limit your changes to only what is required to implement the fix or feature. In particular, avoid style or formatting tools that may modify the formatting of other areas of the code.
- Use descriptive commit titles/messages. "feat: implemented \<feature\>" or "fix: \<problem\> is better than "Updated \<file\>".
- Make sure the code you submit compiles and runs without issues. When we set up unit tests and continuous integration we also expect that the pull request should pass all tests.
- Use [closing keywords][github-help-closing-keywords] in the appropriate section of our Pull Request template where applicable.
- Follow our coding conventions, which we've intentionally kept quite minimal.



### Coding Conventions
**Naming convention**:
  - For class names we use pascal snake case: **`Class_Name`**.
  - For functions we use pascal case: **`FunctionName`**.

  - For (scoped) variables and function parameters we use camel case: **`variableName`** and **`parameterName`**.

  - For class variables we use the Hungarian notation:
    - Class member variables get the 'm_' prefix: **`m_ClassMemberVariableName`**.
    - Class static variables get the 's_' prefix: **`s_ClassStaticVariableName`**.

  - For macros and pre-processor definitions we use capitalized snake case: **`MACRO_NAME`**.
    - If it is specifically related to Ephemeral, we add the 'EPH_' prefix: **`EPH_MACRO_NAME`**.
    - If there is a macro for the application and for the engine, we add an additional 'CORE_' prefix to the engine macro:  **`EPH_CORE_MACRO_NAME`**.

- Use tabs for indentation, not spaces.

- When in doubt, match the code that's already there.



## License
Your submitted code should be **MIT** licensed. The GitHub ToS (and the fact that your fork also contains our LICENSE file) ensures this, so we won't ask when you submit a pull request, but keep this in mind.

For simplicity, the first time you make a pull request, we'll ask you to explicitly state that you agree to **MIT** license it.
