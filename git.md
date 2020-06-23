[<- back](README.md)

# Git on Windows
1. Install Git on Windows
2. Configure Git
3. Set Git for local project (no server)
4. Commits and branches
5. References

## 1. Install Git on Windows
Download and install from https://gitforwindows.org/


## 2. Configure Git
Activate the color in Git. It should only be done once, and it helps the readability of the messages in the console.
```console
git config --global color.diff auto
git config --global color.status auto
git config --global color.branch auto
```
Configure your nickname:
```console
git config --global user.name "fauresystems"
```
Configure your email:
```console
git config --global user.email dev@faure.systems
```


## 3. Local Git (no server)
Git server isn't required to control source code locally.
Create new repository (folder managed with Git):
```console
cd project_folder
git init
```


## 4. Commits and branches
*Commits* should be done several times a day, description to be a single line.

New *branch* is created when code modification will take a long time, then a *merge* is done (to *master* branch) when job is ready.

Quick guide (<a href="https://rogerdudler.github.io/git-guide/index.fr.html" target="_blank">git - petit guide</a>).


## 5. References
* <a href="https://openclassrooms.com/fr/courses/1233741-gerez-vos-codes-source-avec-git" target="_blank">Tutorial openClassRooms *(Gérer vos codes sources avec Git)*</a>
* <a href="https://www.hostinger.fr/tutoriels/tuto-git/" target="_blank">*Tuto GIT pour une prise en main rapide*</a>


## Author

**Faure Systems** (Oct 9th, 2019)
* company: FAURE SYSTEMS SAS
* mail: dev at faure dot systems
* github: <a href="https://github.com/fauresystems?tab=repositories" target="_blank">fauresystems</a>
* web: <a href="https://faure.systems/" target="_blank">Faure Systems</a>