on it...
https://starrymind.tistory.com/162

```console
$ sudo usermod -a -G chrome-remote-desktop {username}
$ /opt/google/chrome-remote-desktop/chrome-remote-desktop --stop
$ sudo cp /opt/google/chrome-remote-desktop/chrome-remote-desktop /opt/google/chrome-remote-desktop/chrome-remote-desktop.orig
$ echo $DISPLAY
$ sudo vim /opt/google/chrome-remote-desktop/chrome-remote-desktop

FIRST_X_DISPLAY_NUMBER = <$DISPLAY>

@staticmethod
def get_unused_display_number():
"""Return a candidate display number for which there is currently no X Server lock file"""
    display = FIRST_X_DISPLAY_NUMBER
    # while os.path.exists(X_LOCK_FILE_TEMPLATE % display):
    #  display += 1
    return display

def launch_session(self, x_args):
    self._init_child_env()
    self._setup_pulseaudio()
    self._setup_gnubby()
    # self._launch_x_server(x_args)
    # if not self._launch_pre_session():
    # If there was no pre-session script, launch the session immediately.
    # self.launch_x_session() 
    # add two lines
    display = self.get_unused_display_number()       
    self.child_env["DISPLAY"] = ":%d" % display

$ /opt/google/chrome-remote-desktop/chrome-remote-desktop --start
```