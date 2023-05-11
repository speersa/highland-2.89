###################################################################
#! /usr/bin/env python
#
# This module is automatically available to python scripts in the
# pilot/scripts directory.
#
# Provide a (simplistic) interface to git commands that uses pipes to
# get information from the locally installed git.

import re
import os.path
from nd280 import shell

def SupportsPartialClones():
    #testString="git version 2.20"
    #versionString = testString.split()[2].split('.')
    versionString = shell.CaptureShell("git --version")[0].split()[2].split('.')
    v=versionString[0]
    r=versionString[1]
    # accept versions >2
    if int(v) > 2 :
        return True
    # reject versions <2
    if int(v) < 2 : 
        return False
    # accept version 2 releases >19 (so 2.20 and higher )
    if int(r) > 19 :
        return True
    return False
def BranchAhead(fetch=True):
    """Check if the current HEAD is ahead of the remote.  This parses
    the git status command to determine if the current HEAD is up to
    date.  It returns an integer that is 0 if the branch is up to
    date, negative if it is behind, and positive if it is ahead.  If
    fetch is false, then this will not try to synchronize with the
    remote."""

    # First fetch from the remote so we have all of the information
    if fetch: shell.Shell("git fetch --all")

    status = shell.CaptureShell("git status -b -s")
    lines = status[0].splitlines()

    match = re.search(r"\[ahead ([0-9])*\]",lines[0])
    if match != None: return int(match.group(1))

    match = re.search(r"\[behind ([0-9])*\]",lines[0])
    if match != None: return int(match.group(1))

    return 0


def BranchModified():
    """Check if there are modified files in the current branch."""
    status = shell.CaptureShell("git status --porcelain")
    lines = status[0].splitlines()
    modified = 0
    for line in lines:
        if line[0] == "M" or line[1] == "M": modified += 1
    return modified


def BranchUntracked():
    """Check if there are untracked files in the current branch."""
    status = shell.CaptureShell("git status --porcelain")
    lines = status[0].splitlines()
    untracked = 0
    for line in lines:
        if line[0] == "?": untracked += 1
    return untracked

def BranchExists(name, path="."):
    """Check that a branch "name" exists in directory located at "path"."""
    try: 
        shell.Shell("cd "+path+"; git show-ref --verify --quiet refs/heads/"+name);
    except:
        return False
    return True
    
def BranchName():
    """Get the name of the current branch."""
    status = shell.CaptureShell("git symbolic-ref HEAD");
    if len(status[0]) > 0: 
    	print (status[0].splitlines()[0])
    	#return os.path.basename(status[0].splitlines()[0]) fails if branch name contains /
    	return status[0].splitlines()[0][11:]
    return "detached"

def GetBranches(glob=None):
    """Get the list of branches in this repository.  If glob is
    provided, then only branches that match the shell glob are
    returned."""
    cmd = "git rev-parse --symbolic --branches"
    if glob != None: cmd += "=" + glob
    status = shell.CaptureShell(cmd)
    if len(status[0]) > 0: return status[0].splitlines()
    return []


def GetTags(glob=None):
    """Get the list of tags in this repository.  If glob is
    provided, then only tags that match the shell glob are
    returned."""
    cmd = "git rev-parse --symbolic --tags"
    if glob != None: cmd += "=" + glob
    status = shell.CaptureShell(cmd)
    if len(status[0]) > 0: return status[0].splitlines()
    return []

def GetRemotes(glob=None):
    """Get the list of remotes for this repository.  If glob is
    provided, then only remote repositories that match the shell glob
    are returned."""
    cmd = "git rev-parse --symbolic --remotes"
    if glob != None: cmd += "=" + glob
    status = shell.CaptureShell(cmd)
    if len(status[0]) > 0: return status[0].splitlines()
    return []

def GetRepositoryRoot():
    """Get the root directory (i.e. the top level directory) of this
    repository.  This returns None if this isn't a git repository."""
    cmd = "git rev-parse --show-toplevel"
    status = shell.CaptureShell(cmd)
    if len(status[0]) > 0: return status[0].splitlines()[0]
    return None
   
def GetUsername():
    """Get the Git username. This returns None if there is no registered
    username."""
    cmd = "git config --global user.name"
    status = shell.CaptureShell(cmd)
    if len(status[0]) > 0: return status[0].splitlines()[0]
    return None
