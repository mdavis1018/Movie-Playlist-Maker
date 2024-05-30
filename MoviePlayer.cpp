/*****************************************
** Description: This file implements the functions outlined in MoviePlayer.h to allow the user to create a movie playlist and sort the movies by year
***********************************************/

#include "MoviePlayer.h"

// Default Constructor
MoviePlayer::MoviePlayer() : m_filename("proj5_movies.txt") {}

// Overloaded Constructor
MoviePlayer::MoviePlayer(string filename) : m_filename(filename) {}

// Destructor
MoviePlayer::~MoviePlayer()
{
  // loop through the movie catalog vector and delete all dynamically allocated movies
  for (size_t i = 0; i < m_movieCatalog.size(); i++)
  {
    delete m_movieCatalog.at(i);
    m_movieCatalog.at(i) = nullptr;
  }
  m_movieCatalog.clear(); // Clear the vector
}

// LoadCatalog
void MoviePlayer::LoadCatalog()
{
  // file stream for reading movie data
  ifstream file;
  file.open(m_filename); // attempt to open file
  if (file.is_open())
  {
    int tracker = 0; // variable to count the number of movies successfully loaded
    string line;

    // variables to store movie members read from file
    string title, rating, genre, director, star, studio, strYear, strRuntime, strBudget, strGross;
    int year, runtime;
    long budget, gross;

    // parsing data using ';' delimeter
    // get line reads up the the DELIMTER = "," and assigns the text read to a variable
    while (getline(file, title, ';'), getline(file, rating, ';'), getline(file, genre, ';'), getline(file, strYear, ';'), getline(file, director, ';'), getline(file, star, ';'), getline(file, strBudget, ';'), getline(file, strGross, ';'), getline(file, studio, ';'), getline(file, strRuntime))
    {
      // Convert string to appropriate types
      year = stoi(strYear);
      runtime = stoi(strRuntime);
      budget = stol(strBudget);
      gross = stol(strGross);
      // Create a new Movie object with the extracted and converted data
      Movie *newMovie = new Movie(title, rating, genre, year, director, star, budget, gross, studio, runtime);
      m_movieCatalog.push_back(newMovie); // Add the new movie to the catalog
      tracker++;                          // update numver
    }
    cout << tracker << " movie files loaded" << endl;
    file.close(); // Close the file after reading all lines
  }
  else
  {
    cout << "Error opening file: " << m_filename << endl;
  }
}

// MainMenu
void MoviePlayer::MainMenu()
{
  int choice;
  do
  {
    cout << "1. Display Movies\n";
    cout << "2. Add Movie to Playlist\n";
    cout << "3. Display Playlist\n";
    cout << "4. Sort Playlist\n";
    cout << "5. Search Movie\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      DisplayMovie();
      break;
    case 2:
      AddMovie();
      break;
    case 3:
      DisplayPlaylist();
      break;
    case 4:
      SortPlaylist();
      break;
    case 5:
      SearchMovie();
      break;
    case 6:
      cout << "Thank you for using the UMBC Movie Player!" << endl;
      break;
    default:
      cout << "Invalid choice, please try again" << endl;
    }
  } while (choice != 6);
}

int MoviePlayer::DisplayMovie()
{
  int year, count = 0;
  string genre;

  // Prompt user for year, ensuring it is within the defined range
  cout << "Which year would you like to display "
       << "(" << MIN_YEAR << "-" << MAX_YEAR << ")"
       << ": ";
  cin >> year;
  while (year < MIN_YEAR || year > MAX_YEAR)
  {
    cout << "Invalid year. Please enter a year between " << MIN_YEAR << " and " << MAX_YEAR << ": ";
    cin >> year;
  }

  cout << "******" << year << "******" << endl;
  // Prompt user for genre (no validation on genre as per requirements)
  cout
      << "Enter a genre: ";
  cin >> ws; // Clear any leading whitespace
  getline(cin, genre);

  cout << "******" << genre << "******" << endl;
  cout << m_movieCatalog.size() << " movies total" << endl;

  // uses iterator to loop through movie catalog
  for (vector<Movie *>::iterator index = m_movieCatalog.begin(); index != m_movieCatalog.end(); ++index)
  {
    // if the movie's year and genre match the user input
    if ((*index)->GetYear() == year && (*index)->GetGenre() == genre)
    {
      // output movie using **
      cout << (index - m_movieCatalog.begin()) + 1 << ": " << **index << endl;
      count++; // increment count
    }
  }

  cout << count << " movies found" << endl;

  // Check if any movies were found
  if (count == 0)
  {
    cout << "No movies found matching the year and genre specified.\n";
  }

  return count; // Return the count of movies found
}

// Add movie function
void MoviePlayer::AddMovie()
{

  DisplayPlaylist(); // output user's playlist

  cout << "Choose the movie you would like to add to the playlist." << endl;
  int displayedMovies = DisplayMovie(); // This function displays movies and returns the count of displayed movies

  if (displayedMovies == 0)
  {
    cout << "No movies available to add. Please try a different search." << endl;
    return; // Exits the function if no movies were found
  }

  int index;
  bool validSelection = false; // bool flag used to break while loop

  while (!validSelection)
  {
    cout << "Enter the index of the movie to add to the playlist: ";
    cin >> index;

    // Validate the index entered by the user
    if (index >= 0 && index < int(m_movieCatalog.size()))
    {
      Movie *selectedMovie = m_movieCatalog[index - 1];
      m_playList.PushBack(selectedMovie);                          // Adds the movie to the playlist using vector's push_back
      cout << *selectedMovie << " added to the playlist." << endl; // Displays the movie added to the playlist using the overloaded << operator
      validSelection = true;                                       // Set to true to exit the loop
    }
    else
    {
      cout << "Invalid index! Please select a valid index from the list above." << endl;
    }
  }
}

void MoviePlayer::DisplayPlaylist()
{
  if (m_playList.IsEmpty())
  {
    cout << "Playlist is currently empty" << endl;
  }
  else
  {
    cout << "Current Playlist:\n";
    for (int i = 0; i < m_playList.GetSize(); i++)
    {
      cout << i + 1 << ". "; // Display the index for clarity
      cout << *(m_playList.At(i)) << endl;
    }
  }
}

void MoviePlayer::SortPlaylist()
{
  // empty playlist
  if (m_playList.IsEmpty())
  {
    cout << "The playlist is empty nothing to sort" << endl;
  }
  // less than two movies in playlist
  else if (m_playList.GetSize() < 2)
  {
    cout << "Error: Cannot sort less than 2 nodes" << endl;
  }
  else
  {
    m_playList.Sort();
    cout << "Done sorting by year\n"
         << m_playList.GetSize() << " items sorted" << endl;
  }
}

void MoviePlayer::StartPlayer()
{
  LoadCatalog(); // Load the movie catalog from the file specified in m_filename
  MainMenu();    // Enter the main menu loop
}

void MoviePlayer::SearchMovie()
{
  int searchType;
  bool validInput = false; // To control the loop based on user input validity

  while (!validInput)
  {
    cout << "What do you want to search by?" << endl;
    cout << "1. Word in Title or Director" << endl;
    cout << "2. Year" << endl;
    cout << "3. Earnings" << endl;
    cout << "Enter choice (1-3): ";
    cin >> searchType;

    // Check if the input is within the valid range
    if (searchType < 1 || searchType > 3)
    {
      cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
    }
    else
    {
      validInput = true; // The input is valid, break the loop
    }
  }

  // Proceed with the valid choice
  switch (searchType)
  {
  case 1:
    SearchByString();
    break;
  case 2:
    SearchByYear();
    break;
  case 3:
    SearchByProfit();
    break;
  default:
    // Although we validated the input, having a default case to handle unexpected scenarios is a good practice.
    cout << "Unexpected error. Please try again." << endl;
    break;
  }
}

// Searches for movies by string in titles or directors
void MoviePlayer::SearchByString()
{
  string searchString;
  cout << "What string would you like to search by? ";
  cin.ignore();               // Ignore the newline character left in the input stream
  getline(cin, searchString); // Get the full line of input

  bool found = false; // Flag to check if any movie matches the search string

  int matches = 0; // track num of matches

  // Iterate through the entire movie catalog
  for (vector<Movie *>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); ++it)
  {
    // Check if the search string is found in the title or director of the movie
    if ((*it)->GetTitle().find(searchString) != string::npos ||
        (*it)->GetDirector().find(searchString) != string::npos)
    {
      matches++;
      cout << matches << ". " << **it << endl; // Print the movie details using the overloaded << operator
      found = true;
    }
  }
  if (!found)
  {
    cout << "No movies found matching the search string.\n";
  }
}

// Searches for movies by  year
void MoviePlayer::SearchByYear()
{
  int year;
  cout << "Enter the year to search for: ";
  cin >> year; // Take year input from user

  bool found = false; // Flag to check if any movies are found

  int matches = 0; // track num of matches

  // Iterate through all movies in the catalog
  for (vector<Movie *>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); ++it)
  {
    // Check if the movie's year matches the user input
    if ((*it)->GetYear() == year)
    {
      matches++;
      cout << matches << ". " << **it << endl; // Display the movie using the overloaded << operator
      found = true;                            // Set the flag to true as we found a match
    }
  }

  if (!found)
  {
    cout << "No movies found from year " << year << endl;
  }
}

void MoviePlayer::SearchByProfit()
{
  long minProfit;
  cout << "Enter minimum profit: ";
  cin >> minProfit; // Take minimum profit input from user

  bool found = false; // Flag to check if any movies meet the profit criteria

  int matches = 0; // track num of matches

  // Iterate through all movies in the catalog
  for (vector<Movie *>::iterator it = m_movieCatalog.begin(); it != m_movieCatalog.end(); ++it)
  {
    // Calculate the profit by subtracting budget from gross
    long profit = (*it)->GetGross() - (*it)->GetBudget();
    // Check if the profit is at least the minimum specified by the user
    if (profit >= minProfit)
    {
      matches++;
      cout << matches << ". " << **it << endl; // Display the movie if it meets the profit criteria
      found = true;                            // Set the flag to true as we found a match
    }
  }

  if (!found)
  {
    cout << "No movies found with a minimum profit of " << minProfit << endl;
  }
}
