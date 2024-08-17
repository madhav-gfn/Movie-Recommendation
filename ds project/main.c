#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Movie {
    char title[100];
    int year;
    float rating;
    char genre[50];
    struct Movie *prev;
    struct Movie *next;
} Movie;

typedef struct WishlistNode {
    Movie *movie;
    struct WishlistNode *next;
} WishlistNode;

typedef struct WishlistStack {
    WishlistNode *top;
} WishlistStack;

typedef struct Queue {
    Movie *front;
    Movie *rear;
} Queue;

Queue* createQueue();
void enqueue(Queue *queue, char title[], int year);
Movie* dequeue(Queue *queue);
void displayUpcomingMovies(Queue *queue);
void loadUpcomingMoviesFromFile(Queue *queue);



Movie* createMovieNode(char title[], int year);
Queue* createQueue();
void enqueue(Queue *queue, char title[], int year);
Movie* dequeue(Queue *queue);
void displayUpcomingMovies(Queue *queue);
void loadUpcomingMoviesFromFile(Queue *queue);
Movie *createMovie(char title[], int year, float rating, char genre[]);
void insertMovie(Movie **head, char title[], int year, float rating, char genre[]);
void displayMovies(Movie *head);
void searchMovie(Movie *head, char title[]);
void addMovieToDatabase(Movie **head);
void recommendMovieByGenre(Movie *head, char genre[]);
void filterMovies(Movie *head, int choice);
void sortMoviesByRating(Movie **head);
Movie *mergeSort(Movie *head);
Movie *merge(Movie *a, Movie *b);
void loadMoviesFromFile(Movie **head);
void saveMoviesToFile(Movie *head);
void recommendMovieByMood(Movie *head);
WishlistStack *createWishlist();
void push(WishlistStack *stack, Movie *movie);
Movie *pop(WishlistStack *stack);
void displayWishlist(WishlistStack *stack);
void saveWishlistToFile(WishlistStack *stack);
void loadWishlistFromFile(WishlistStack *stack);
void frontBackSplit(Movie *source, Movie **frontRef, Movie **backRef);

int main()
{
    Movie *head = NULL;
    WishlistStack *wishlist = createWishlist();
    Queue *upcomingMoviesQueue = createQueue();
    
    loadMoviesFromFile(&head);
    loadWishlistFromFile(wishlist);
    loadUpcomingMoviesFromFile(upcomingMoviesQueue);
    int choice;
    char title[100];
    char genre[50];

    do
    {
        printf("\nMovie Recommendation System\n");
        printf("1. Add a movie to the database\n");
        printf("2. Show all movies\n");
        printf("3. Search for a movie\n");
        printf("4. Recommend movie by genre\n");
        printf("5. Filter movies\n");
        printf("6. See top 25 movies by rating\n");
        printf("7. Recommend a movie by mood\n");
        printf("8. Add a movie to wishlist\n");
        printf("9. View wishlist\n");
        printf("10. Remove a movie from wishlist\n");
        printf("11. Show upcoming movies\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addMovieToDatabase(&head);
            break;
        case 2:
            displayMovies(head);
            break;
        case 3:
            printf("Enter the title of the movie to search: ");
            scanf(" %[^\n]", title);
            searchMovie(head, title);
            break;
        case 4:
            printf("Enter the genre to recommend a movie: ");
            scanf(" %[^\n]", genre);
            recommendMovieByGenre(head, genre);
            break;
        case 5:
            printf("Filter movies by:\n");
            printf("1. Year\n");
            printf("2. Rating\n");
            printf("3. Genre\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            filterMovies(head, choice);
            break;
        case 6:
            sortMoviesByRating(&head);
            break;
        case 7:
            recommendMovieByMood(head);
            break;
        case 8:
            addMovieToWishlist(wishlist, head);
            break;

        case 9:
            displayWishlist(wishlist);
            break;
        case 10:
            if (wishlist->top != NULL)
            {
                Movie *movieToRemove = pop(wishlist);
                printf("Movie removed from wishlist:\n");
                printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", movieToRemove->title, movieToRemove->year, movieToRemove->rating, movieToRemove->genre);
                free(movieToRemove);
                saveWishlistToFile(wishlist);
            }
            else
            {
                printf("Wishlist is empty.\n");
            }
            break;
        case 11:
            displayUpcomingMovies(upcomingMoviesQueue);
            break;
        case 12:
            printf("Exiting...");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 11);

    
    saveMoviesToFile(head);
    free(wishlist);

    return 0;
}


void addMovieToWishlist(WishlistStack *wishlist, Movie *database) {
    char title[100];
    printf("Enter the title of the movie to add to the wishlist: ");
    scanf(" %[^\n]", title);

    Movie *movieToAdd = NULL;
    Movie *temp = database;

    while (temp != NULL) {
        if (strstr(temp->title, title) != NULL) {
            movieToAdd = temp;
            break;
        }
        temp = temp->next;
    }

    if (movieToAdd != NULL) {
        printf("Movie found:\n");
        printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", movieToAdd->title, movieToAdd->year, movieToAdd->rating, movieToAdd->genre);
        push(wishlist, movieToAdd);
        printf("Movie added to the wishlist.\n");
        saveWishlistToFile(wishlist);
    } else {
        printf("Movie not found in the database.\n");
    }
}



Movie *createMovie(char title[], int year, float rating, char genre[])
{
    Movie *newmovie = (Movie *)malloc(sizeof(Movie));
    if (newmovie != NULL)
    {
        strcpy(newmovie->title, title);
        newmovie->year = year;
        newmovie->rating = rating;
        strcpy(newmovie->genre, genre);
        newmovie->prev = NULL;
        newmovie->next = NULL;
    }
    return newmovie;
}
Movie* createMovieNode(char title[], int year) {
    Movie *newMovie = (Movie*)malloc(sizeof(Movie)); // Allocate 7memory for a pointer to Movie
    if (newMovie != NULL) {
        strcpy(newMovie->title, title);
        newMovie->year = year;
        newMovie->next = NULL;
    }
    return newMovie;
}

Queue* createQueue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue)); // Allocate memory for a pointer to Queue
    if (queue != NULL) {
        queue->front = NULL;
        queue->rear = NULL;
    }
    return queue;
}



void enqueue(Queue *queue, char title[], int year) {
    Movie *newmovie = createMovieNode(title, year);
    if (queue->rear == NULL) {
        queue->front = newmovie;
        queue->rear = newmovie;
    } else {
        queue->rear->next = newmovie;
        queue->rear = newmovie;
    }
}


Movie* dequeue(Queue *queue) {
    if (queue->front == NULL) {
        return NULL; // Queue is empty
    } else {
        Movie *temp = queue->front;
        queue->front = queue->front->next;
        if (queue->front == NULL) {
            queue->rear = NULL;
        }
        return temp;
    }
}


void displayUpcomingMovies(Queue *queue) {
    if (queue->front == NULL) {
        printf("No upcoming movies.\n");
    } else {
        printf("\nUpcoming Movies:\n");
        Movie *current = queue->front;
        while (current != NULL) {
            printf("Title: %s | Year: %d\n", current->title, current->year);
            current = current->next;
        }
    }
}


void loadUpcomingMoviesFromFile(Queue *queue) {
    FILE *file = fopen("upcoming_movies.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char title[100];
    int year;

    while (fscanf(file, "%[^|]| %d\n", title, &year) != EOF) {
        enqueue(queue, title, year);
    }

    fclose(file);
}


void insertMovie(Movie **head, char title[], int year, float rating, char genre[])
{
    Movie *newmovie = createMovie(title, year, rating, genre);
    if (newmovie != NULL)
    {
        if (*head == NULL)
        {
            *head = newmovie;
        }
        else
        {
            newmovie->next = *head;
            (*head)->prev = newmovie;
            *head = newmovie;
        }
    }
}

void displayMovies(Movie *head)
{
    if (head == NULL)
    {
        printf("No movies in the database.\n");
        return;
    }

    int page = 1;
    int totalPages = 0;
    Movie *current = head;
    int count = 0;

    
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    
    totalPages = (count + 9) / 10;

    do
    {
        printf("\nMovies (Page %d/%d):\n", page, totalPages);
        int moviesDisplayed = 0;

        
        while (head != NULL && moviesDisplayed < 10)
        {
            printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", head->title, head->year, head->rating, head->genre);
            head = head->next;
            moviesDisplayed++;
        }

        printf("\n");

        
        if (page > 1)
        {
            printf("Press 'p' for Previous Page | ");
        }

        if (page < totalPages)
        {
            printf("Press 'n' for Next Page | ");
        }

        printf("Press 'b' to go Back\n");

        
        char choice;
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        if (choice == 'p' && page > 1)
        {
            page--;
        }
        else if (choice == 'n' && page < totalPages)
        {
            page++;
        }
        else if (choice == 'b')
        {
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }

        
        current = head;
    } while (1);
}


void searchMovie(Movie *head, char title[])
{
    int found = 0;
    while (head != NULL)
    {
        
        if (strstr(head->title, title) != NULL)
        {
            printf("Movie found:\n");
            printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", head->title, head->year, head->rating, head->genre);
            found = 1;
        }
        head = head->next;
    }
    if (!found)
    {
        printf("No matching movies found.\n");
    }
}


void addMovieToDatabase(Movie **head)
{
    char title[100];
    int year;
    float rating;
    char genre[50];

    printf("Enter movie title: ");
    scanf(" %[^\n]", title);
    printf("Enter movie year: ");
    scanf("%d", &year);
    printf("Enter movie rating: ");
    scanf("%f", &rating);
    printf("Enter movie genre: ");
    scanf(" %[^\n]", genre);

    insertMovie(head, title, year, rating, genre);
    printf("Movie added successfully.\n");
}


void recommendMovieByGenre(Movie *head, char genre[])
{
    printf("Recommended movies in genre \"%s\":\n", genre);
    while (head != NULL)
    {
        if (strstr(head->genre, genre) != NULL)
        {
            printf("Title: %s | Year: %d | Rating: %.1f\n", head->title, head->year, head->rating);
        }
        head = head->next;
    }
}


void filterMovies(Movie *head, int choice)
{
    switch (choice)
    {
    case 1:
    {
        int year;
        printf("Enter the year to filter movies: ");
        scanf("%d", &year);
        printf("Movies released in year %d:\n", year);
        while (head != NULL)
        {
            if (head->year == year)
            {
                printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", head->title, head->year, head->rating, head->genre);
            }
            head = head->next;
        }
        break;
    }
    case 2:
    {
        float rating;
        printf("Enter the minimum rating to filter movies: ");
        scanf("%f", &rating);
        printf("Movies with rating greater than %.1f:\n", rating);
        while (head != NULL)
        {
            if (head->rating > rating)
            {
                printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", head->title, head->year, head->rating, head->genre);
            }
            head = head->next;
        }
        break;
    }
    case 3:
    {
        char genre[50];
        printf("Enter the genre to filter movies: ");
        scanf(" %[^\n]", genre);
        printf("Movies in genre \"%s\":\n", genre);
        while (head != NULL)
        {
            if (strstr(head->genre, genre) != NULL)
            {
                printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", head->title, head->year, head->rating, head->genre);
            }
            head = head->next;
        }
        break;
    }
    default:
        printf("Invalid choice!\n");
    }
}



void recommendMovieByMood(Movie *head) {
    int mood;
    int recency;
    int ratingPref;

    printf("\nHow do you feel today?\n");
    printf("1. Dramatic (Action, Adventure, Drama)\n");
    printf("2. Intense (Horror, Thriller)\n");
    printf("3. Gentle (Comedy, Family, Romance)\n");
    printf("4. Curious (History, Mystery)\n");
    printf("5. Out of this world (Fantasy, Science-Fiction)\n");
    printf("6. Realistic (Documentary)\n");
    printf("Enter your mood: ");
    scanf("%d", &mood);

    printf("\nIs the movie recent?\n");
    printf("1. Recent (2015-2024)\n");
    printf("2. Older (before 2015)\n");
    printf("Enter your choice: ");
    scanf("%d", &recency);

    printf("\nDo you prefer high rated or low rated movies?\n");
    printf("1. High rated (>7.5)\n");
    printf("2. Low rated (<7.5)\n");
    printf("Enter your preference: ");
    scanf("%d", &ratingPref);

    Movie *filteredMovies = NULL;
    while (head != NULL) {
        int recent = (recency == 1) ? (head->year >= 2015) : (head->year < 2015);
        int highRated = (ratingPref == 1) ? (head->rating > 7.5) : (head->rating < 7.5);

        if (recent && highRated) {
            if ((mood == 1 && strstr(head->genre, "Action") != NULL) ||
                (mood == 1 && strstr(head->genre, "Adventure") != NULL) ||
                (mood == 1 && strstr(head->genre, "Drama") != NULL) ||
                (mood == 2 && strstr(head->genre, "Horror") != NULL) ||
                (mood == 2 && strstr(head->genre, "Thriller") != NULL) ||
                (mood == 3 && strstr(head->genre, "Comedy") != NULL) ||
                (mood == 3 && strstr(head->genre, "Family") != NULL) ||
                (mood == 3 && strstr(head->genre, "Romance") != NULL) ||
                (mood == 4 && strstr(head->genre, "History") != NULL) ||
                (mood == 4 && strstr(head->genre, "Mystery") != NULL) ||
                (mood == 5 && strstr(head->genre, "Fantasy") != NULL) ||
                (mood == 5 && strstr(head->genre, "Science-Fiction") != NULL) ||
                (mood == 6 && strstr(head->genre, "Documentary") != NULL)) {
                insertMovie(&filteredMovies, head->title, head->year, head->rating, head->genre);
            }
        }
        head = head->next;
    }

    if (filteredMovies == NULL) {
        printf("Sorry, no movie found matching your criteria.\n");
    } else {
        
        int count = 0;
        Movie *temp = filteredMovies;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }

        
        srand(time(NULL));
        int randomIndex = rand() % count;

        
        temp = filteredMovies;
        for (int i = 0; i < randomIndex; i++) {
            temp = temp->next;
        }

        printf("\nRecommended movie:\n");
        printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", temp->title, temp->year, temp->rating, temp->genre);

        
        while (filteredMovies != NULL) {
            Movie *temp = filteredMovies;
            filteredMovies = filteredMovies->next;
            free(temp);
        }
    }
}



void sortMoviesByRating(Movie **head)
{
    Movie *sortedList = mergeSort(*head);
    displayMovies(sortedList);
    free(sortedList); 
}


Movie *mergeSort(Movie *head)
{
    Movie *a;
    Movie *b;

    
    if ((head == NULL) || (head->next == NULL))
    {
        return head;
    }

    
    frontBackSplit(head, &a, &b);

    
    a = mergeSort(a);
    b = mergeSort(b);

    
    return merge(a, b);
}


void frontBackSplit(Movie *source, Movie **frontRef, Movie **backRef)
{
    Movie *fast;
    Movie *slow;
    slow = source;
    fast = source->next;

    
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

Movie *merge(Movie *a, Movie *b)
{
    Movie *result = NULL;

    if (a == NULL)
    {
        return b;
    }
    else if (b == NULL)
    {
        return a;
    }

    if (a->rating >= b->rating)
    {
        result = a;
        result->next = merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = merge(a, b->next);
    }

    return result;
}

void displayTop25Movies(Movie *head)
{
    printf("\nTop 25 Movies by Rating:\n");
    int count = 0;
    while (head != NULL && count < 25)
    {
        printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", head->title, head->year, head->rating, head->genre);
        head = head->next;
        count++;
    }
}

void loadMoviesFromFile(Movie **head)
{
    FILE *file = fopen("database.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char title[100];
    int year;
    float rating;
    char genre[50];

    while (fscanf(file, "%[^|]| %d | %f | %[^\n]\n", title, &year, &rating, genre) != EOF)
    {
        insertMovie(head, title, year, rating, genre);
    }

    fclose(file);
}

void saveMoviesToFile(Movie *head)
{
    FILE *file = fopen("database.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    while (head != NULL)
    {
        fprintf(file, "%s | %d | %.1f | %s\n", head->title, head->year, head->rating, head->genre);
        head = head->next;
    }

    fclose(file);
}

WishlistStack *createWishlist()
{
    WishlistStack *stack = (WishlistStack *)malloc(sizeof(WishlistStack));
    if (stack != NULL)
    {
        stack->top = NULL;
    }
    return stack;
}


void push(WishlistStack *stack, Movie *movie)
{
    WishlistNode *newNode = (WishlistNode *)malloc(sizeof(WishlistNode));
    if (newNode != NULL)
    {
        newNode->movie = movie;
        newNode->next = stack->top;
        stack->top = newNode;
    }
}


Movie *pop(WishlistStack *stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }
    WishlistNode *temp = stack->top;
    stack->top = stack->top->next;
    Movie *poppedMovie = temp->movie;
    free(temp);
    return poppedMovie;
}


void displayWishlist(WishlistStack *stack)
{
    if (stack->top == NULL)
    {
        printf("Wishlist is empty.\n");
        return;
    }
    printf("\nMovies in Wishlist:\n");
    WishlistNode *current = stack->top;
    while (current != NULL)
    {
        printf("Title: %s | Year: %d | Rating: %.1f | Genre: %s\n", current->movie->title, current->movie->year, current->movie->rating, current->movie->genre);
        current = current->next;
    }
}


void saveWishlistToFile(WishlistStack *stack)
{
    FILE *file = fopen("wishlist.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    WishlistNode *current = stack->top;
    while (current != NULL)
    {
        fprintf(file, "%s | %d | %.1f | %s\n", current->movie->title, current->movie->year, current->movie->rating, current->movie->genre);
        current = current->next;
    }
    fclose(file);
}




void loadWishlistFromFile(WishlistStack *stack)
{
    FILE *file = fopen("wishlist.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    char title[100];
    int year;
    float rating;
    char genre[50];
    while (fscanf(file, "%[^|]| %d | %f | %[^\n]\n", title, &year, &rating, genre) != EOF)
    {
        Movie *movie = createMovie(title, year, rating, genre);
        push(stack, movie);
    }
    fclose(file);
}