
# Algorithm

1. **Start**

2. **Display Menu and Wait for Command**
   - **Repeat** until user exits:
     - **Input** command from user.

3. **Process Command**
   - **If** command is `add <text>`:
     - Add line with `<text>`.
     - Display updated content.
    - **Else if** command is `add -m`:
	     - Prompt user to enter multiple lines.
	     - Display updated content.
    - **Else if** command is `add -a <line_number>`:
	     - Validate line number.
       - Add line above <line_number>
	     - Display updated content.
   - **Else if** command is `add -b <line_number>`:
	     - Validate line number.
       - Add line below <line_number>.
	     - Display updated content.
   - **Else if** command is `edit <line number>`:
     - Validate line number.
     - Edit specified line.
     - Display updated content.
   - **Else if** command is `del <line number>`:
     - Validate line number.
     - Delete specified line.
     - Display updated content.
   - **Else if** command is `del -a`:
     - Confirm and delete all lines.
     - Display empty content.
   - **Else if** command is `save`:
     - Save lines to file.
     - Display success message.
   - **Else if** command is `open <filename>`:
     - Read lines from file.
     - Display updated content.
   - **Else if** command is `display`:
     - Display current content.
   - **Else if** command is `menu`:
     - Show available commands.
   - **Else if** command is `exit`:
     - Exit program.
   - **Else**:
     - Print invalid command message.

4. **End**
