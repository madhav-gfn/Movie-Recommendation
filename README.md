# Movie Recommendation System

[![GitHub](https://img.shields.io/badge/GitHub-madhav__gfn-blue?style=flat-square&logo=github)](https://github.com/madhav_gfn)

A comprehensive movie recommendation system implemented in C, offering various features for movie enthusiasts.

## Features

- Add movies to the database
- Display all movies
- Search for specific movies
- Recommend movies by genre
- Filter movies by year, rating, or genre
- Sort and display top-rated movies
- Recommend movies based on mood
- Manage a personal movie wishlist
- View upcoming movie releases

## Getting Started

### Prerequisites

- GCC compiler
- Standard C libraries

### Compilation

To compile the program, use the following command:

```bash
gcc -o movie_recommender main.c
```

### Running the Program

After compilation, run the program using:

```bash
./movie_recommender
```

## Usage

The program presents a menu-driven interface. Simply follow the on-screen prompts to:

1. Add new movies to the database
2. View all movies in the system
3. Search for specific movies
4. Get movie recommendations based on genre or mood
5. Filter and sort movies
6. Manage your movie wishlist
7. Check upcoming movie releases

## Data Persistence

The system uses file I/O to maintain persistence:
- Movie database is saved to and loaded from `database.txt`
- Wishlist is saved to and loaded from `wishlist.txt`
- Upcoming movies are loaded from `upcoming_movies.txt`

## Contributing

Contributions to enhance the functionality or efficiency of the system are welcome. Please feel free to fork the repository and submit pull requests.

## License

This project is open-source and available under the MIT License.

## Contact

For any queries or suggestions, please open an issue on the GitHub repository.

---

Happy movie browsing!

