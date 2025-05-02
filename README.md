# Git Simulator

## Overview
This Git Simulator is a C++ application that mimics basic functionality of GitHub, allowing users to manage accounts, repositories, and social interactions in a simplified way. The project was developed by Omima Shah and Urwa Sajid.

## Features

### User Management
- **Login/Logout**: Secure authentication system
- **Add User**: Create new user accounts with username, password, and email
- **Remove User**: Delete existing user accounts

### Repository Management
- **Add Repository**: Create new repositories under your account
- **Remove Repository**: Delete existing repositories
- **View Repositories**: List all repositories owned by a user
- **Commit**: Update repository with commit messages
- **Fork Repository**: Copy another user's repository to your account

### Social Features
- **Add Follower**: Follow other users
- **Remove Follower**: Unfollow users
- **View Followers**: See who follows a specific user
- **View User**: Display comprehensive user information including repositories and followers

## Data Structures
- **AVL Tree**: Used for efficient user management and searching
- **Linked Lists**: Used to store repositories and followers
- **Hash Map**: Quick username/password verification

## File Management
The simulator uses CSV files to persist data:
- `login.csv`: Stores user credentials (username, password, email)
- `[username].csv`: Stores repository information for each user

## How to Use

1. **Compile the Program**:
   ```bash
   g++ project.cpp -o git_simulator
   ```

2. **Run the Application**:
   ```bash
   ./git_simulator
   ```

3. **Available Commands**:
   - `login`: Sign in to your account
   - `adduser`: Create a new user account
   - `removeuser`: Delete an existing user
   - `addrepository`: Create a new repository
   - `removerepository`: Delete an existing repository
   - `viewrepositories`: List all repositories
   - `viewfollowers`: See followers
   - `addfollower`: Follow another user
   - `removefollower`: Unfollow a user
   - `viewuser`: Display user information
   - `commit`: Update repository with commit message
   - `forkrepo`: Copy another user's repository
   - `logout`: Sign out from current session
   - `exit`: Close the application

## Implementation Details

The project implements several key components:
- User authentication and management
- Repository creation and management
- Social network interactions
- Data persistence through file operations
- Efficient data retrieval using AVL tree structure

## Future Enhancements
- Pull requests functionality
- Branch management
- Collaboration features
- Graphical user interface
- Enhanced security features