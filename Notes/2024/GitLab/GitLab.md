GitLab
===

docker pull gitlab/gitlab-ee:16.9.6-ee.0

https://docs.gitlab.com/ee/install/docker.html
https://docs.gitlab.com/omnibus/settings/configuration.html
https://docs.gitlab.com/omnibus/settings/ssl/

```
git clone --mirror <src_git>
cd <src_git>.git
git remote set-url --push origin <dst_git>
git push --mirror
```