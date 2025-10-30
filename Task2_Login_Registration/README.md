# Login & Registration System

The Login and Registration System allows users to securely register and log in  
using a simple text-based interface. Each user has a dedicated file in the `users/`  
directory (one file per user), where credentials are stored.

The program works on both Windows and Linux/macOS systems,  
automatically creating the `users/` folder if it does not exist.

## Program Logic

1. **Registration**
   - Prompts for a username and password.
   - Validates both inputs (length >= 3, no spaces).
   - Checks if a user file already exists (`users/<username>.txt`).
   - If not found, creates a new file containing the password.

2. **Login**
   - Prompts for existing username and password.
   - Verifies user existence.
   - Reads stored password from file and compares with input.
   - Displays appropriate success or error messages.

3. **Folder Management**
   - Uses platform-specific folder creation:
     - On Windows: `if not exist users mkdir users`
     - On Linux/macOS: `mkdir -p users`


## Running the Program

g++ lr.cpp -o lr
./lr

## Example Interaction

====== LOGIN & REGISTRATION SYSTEM ======
1. Register
2. Login
3. Exit
Choose option: 1
Enter username: gabriel
Enter password: secret123
User 'gabriel' registered successfully.

Choose option: 2
Enter username: gabriel
Enter password: secret123
Login successful! Welcome back, gabriel.
