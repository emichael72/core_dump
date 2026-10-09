# Core Dump

A small C command-line program used to demonstrate how a coding agent makes a change and hands it back for review.

Each feature is a separate module. That keeps a new task small enough to follow: write the code, add an option, document it, and test it.

The agents and the PR gate live in the [agents repository](https://github.com/emichael72/agents). This repository is the project they work on.

## Build and try it

On Linux, with a C compiler and GNU Make installed:

~~~sh
make
./core_dump --help
./core_dump --pi
make check
~~~

The executable is `core_dump`. Build files go into `build/`; `make clean` removes both. Running without arguments shows help. You can combine options, and they run in command-line order.

## Available commands

| Example | What it does |
| --- | --- |
| `./core_dump --pi` | Prints pi to 15 decimal places |

The pi module is the example to follow: each new feature is another module beside it.

Use `--help` for short options and other usage details.

## Add a module

The structure is straightforward:

~~~text
src/main.c       Options, help text, and module dispatch
src/include/     Module headers
src/modules/     Module implementations
Makefile         Build rules and the check target
~~~

Add the implementation and header, then update the help text, long-option table, `short_options` string, and dispatch in `main.c`. The Makefile discovers module C files automatically.

Add tests to `make check`, including an invalid input that should fail. Give new files a Doxygen `@file` block and document functions, parameters, and return values. Follow the existing pattern and avoid documenting the same function twice.

## Submit a change

Open a pull request against main. When working through an agent, the pr tool handles the branch, commit, push, and PR. It runs the code checks before submitting.

The separate gate service then assesses the committed version:

1. Build it, run its tests, and check its Doxygen documentation using the agents' shared shell and doxy tools.
2. Ask the model for a short quiz about the diff.
3. Put the quiz link in the PR's `developer-quiz` status and comment.
4. Grade the developer's answers and report the result to GitHub.

Open the status's Details link to take the quiz. Every answer must be correct; retries are allowed. Build or documentation failures need a code fix and another push.

GitHub enforces the required `developer-quiz` status. Passing satisfies that requirement; a person still merges the PR once the other requirements are met. A changed PR or base revision needs a new assessment.

Cosmetic-only changes can pass without a quiz. The demo gate also supports a skip option, currently enabled in its checked-in settings; turn it off to require the quiz for code changes.

See the [gate README](https://github.com/emichael72/agents/blob/develop/gatekeepers/pr/README.md) and its [walkthrough](https://github.com/emichael72/agents/blob/develop/gatekeepers/pr/README.md#what-happens-to-a-change) for the service, database, and GitHub handoff.
