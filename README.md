# Risk Game

## Development

### While working on a feature

* Create a branch from `a#_final` (dev branch) where # is the assignment number.
```
git checkout -b "Branch_Name"
```

* Atomic commits: Every change you make should have its on separate commit.

* Commit messages should be short but clear.


### Done implementing your Feature?

* Commit your changes.

* Update local  `a#_final` branch

```
git checkout dev
git pull
```

* merge  `a#_final` on your branch

```
git checkout <your branch>
git  pull   a#_final
```

### Pull Requests

* Open a pull request for your branch based on the develop branch and add everyone as a reviewer.


* Once you get an approval, go ahead and merge (Make sure to select the option to close/delete the branch + Squash commits ).

#### Pull Request format

If your PR is for a Feature:

* Summary
* Technical Description
* Attachments (screenshots, diagrams, results, etc)

If your PR is for a bug:

* Observation
* Reproduction Steps
* Resolution Description
* Resolution Validation