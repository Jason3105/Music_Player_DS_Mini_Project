# 🎵 Data Structure Mini Project: Spotify-Like Algorithm-Based Music Player

This project implements a music player using linked lists to manage a playlist, inspired by Spotify-like functionalities. It allows users to add, play, delete, and shuffle songs in a dynamic playlist while leveraging system commands to play .mp3 files using the default media player.

📋 Features  
1. Add Songs: Add new .mp3 songs to the playlist and save them to a file (songs.txt).  
2. Play Songs: Play selected songs or navigate through the playlist using:  
&nbsp;- Play Next  
&nbsp;- Play Previous  
&nbsp;- Play Selected Song  
3. Shuffle Play: Randomly select and play a song from the playlist.  
4. Delete Songs: Delete songs from the playlist.  
5. Display Playlist: View the current playlist.  
6. Persistent Storage: Songs are stored in songs.txt and loaded on startup.

🛠️ Data Structures Used  

&nbsp;- Doubly Linked List: Manages the dynamic playlist, allowing forward and backward navigation.  
&nbsp;- File Handling: Loads and saves songs to songs.txt for persistent storage.  

🚀 How to Run the Project  
1. Prerequisites  
&nbsp;- Operating System: Windows, macOS, or Linux.  
&nbsp;- C Compiler: gcc (MinGW for Windows or GCC for macOS/Linux).  
2. Clone the Repository  
git clone https://github.com/yourusername/spotify-algorithm-music-player.git  
cd spotify-algorithm-music-player  
3. Compile the Code  
gcc music_player.c -o music_player  
4. Create a songs.txt File  
Add the full paths of your .mp3 files to songs.txt. For example:
C:\\Users\\jason\\Music\\sairat.mp3  
C:\\Users\\jason\\Music\\Espresso.mp3  
C:\\Users\\jason\\Music\\story_of_my_life.mp3  
5. Run the Program  
./music_player  

📄 Usage Instructions

Upon running the program, you'll see a menu like this:  
1. Play Next  
2. Play Previous  
3. Play Selected Song  
4. Shuffle Play  
5. Display Playlist  
6. Add New Song   
7. Delete Song  
8. Exit  

Menu Options  
1. Play Next: Play the next song in the playlist.  
2. Play Previous: Play the previous song in the playlist.  
3. Play Selected Song: Enter the song number to play that song.  
4. Shuffle Play: Play a random song from the playlist.  
5. Display Playlist: Show all songs in the current playlist.  
6. Add New Song: Add a new .mp3 song by entering its full path.  
7. Delete Song: Delete a song by specifying its number.  
8. Exit: Exit the program.  

🖥️ Example Session

Playlist:  
1. C:\Users\jason\Music\sairat.mp3  
2. C:\Users\jason\Music\Espresso.mp3  

1. Play Next  
2. Play Previous  
3. Play Selected Song  
4. Shuffle Play  
5. Display Playlist  
6. Add New Song  
7. Delete Song  
8. Exit  
Enter your choice: 3  
Enter the song number to play: 2 
Attempting to play: C:\Users\jason\Music\Espresso.mp3  

📝 Project Structure

├── prototype.c    # Main source code file  
├── songs.txt         # File storing the playlist (full paths of .mp3 files)  
└── README.md         # Project documentation  

⚠️ Notes

Ensure your .mp3 file paths are correct.  
For Windows, paths should use double backslashes (\\) or forward slashes (/).  
The program uses the system's default media player to play songs.  
