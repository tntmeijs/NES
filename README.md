# C++ NES emulator
Hi and welcome to the homepage of my C++ NES emulator.
The goal of this project is to provide a solid C++ reference for a NES emulator.
Most emulators you will find online are complex and lack proper documentation.

This project shows a possible implementation of a NES emulator using modern C++ (11/14/17).

It is very much a work in progress right now, but be sure to star this repository to stay up-to-date on any new developments.

If time allows, I will write a detailed tutorial that covers everything from the absolute basics all the way to getting an image on screen. Almost none of the tutorials out there do so, and those that do are either outdated or incomplete.

# Building
1. `mkdir build`
2. `cmake ..`
3. ??
4. Profit.

Since we use WxWidgets, we have one additional step.
The GUI library works natively on each platform.
To build and run under windows, go to `Project Settings > Linker > System > SubSystem` and select `/SUBSYSTEM:WINDOWS`.
Most of the time CMake will default to the console subsystem, which is why it is important to double-check this.

# Commits
Each commit follows the same naming standard:
```
Message here without a period
[ADD] When you add new things, use proper punctuation.
[CHANGE] When you change things, use proper punctuation.
[DELETE] When you delete things, use proper punctuation.
```

# Branches
- The project's master branch has been locked. Nobody should commit on master unless merging a Pull Request.
- Pull Requests can only be merged into master by @tntmeijs.
- Make sure to follow the commit guide in the "contributing" section below.

# Contributing
As the complexity of this project increases, so does the need for a proper commit guide.
The following rules need to be followed in order to make a commit:
1. Check whether there is an issue for the task you will be working on.
   1. If there isn't, create a new issue.
2. Create a new feature branch using the following format: `feature/<issue id>-<issue name>`
   1. Make sure the branch uses dashes `-` as spaces.
   2. Ensure that the id and name both match the issue to make it easy to track work.
   3. Clone the new branch.
3. Start development.
4. Create a new **DRAFT** Pull Request to show others that you've started working on it.
   
   It is recommended to create a draft Pull Request as early into development as possible to ensure that other contributers can give feedback on the code as you work on it.
5. Make sure all tests pass.
6. Update your Pull Request and ask for a review.
   1. Make sure your Pull Request has a proper name.
7. Fix any problems.
8.  Merge into master, do not rebase or anything like that. We would like to preserve the history.

Please note that this project is still in its very early stages. A code style guide, as well as a CI/CD pipeline will be added in the future. In the meanwhile, we would like to ask you to pay close attention to this README and follow the instructions given.

Thank you.

# Project structure
| Folder                                    | Description                                               |
| ----------------------------------------- | --------------------------------------------------------- |
| [./](/)                                   | Root folder of this project.                              |
| [./_deps](/_deps)                         | Third-party libraries.                                    |
| [./cpu](/cpu)                             | Main CPU emulator class.                                  |
| [./cpu/flags](/cpu/flags)                 | Various enums used to emulate the flags of a 6502 CPU.    |
| [./cpu/instructions](cpu/instructions)    | CPU opcode implementations.                               |
| [./editor](/editor)                       | Main editor class.                                        |
| [./editor/ui](/editor/ui)                 | Editor UI components that makes up the complete editor.   |
| [./io](/io)                               | iNES file format implementation and rom loading.          |
| [./ram](/ram)                             | Representation of the NES' RAM.                           |
| [./utility](/utility)                     | Useful functions and miscellaneous helpers.               |
