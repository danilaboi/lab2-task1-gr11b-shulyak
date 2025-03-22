#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void task1() {
  printf("\n==== ЗАДАЧА 1: Числа без одинаковых цифр ====\n");

  int n;
  printf("Введите количество чисел (n): ");
  scanf("%d", &n);

  int numbers[n];
  srand(time(NULL));
  printf("Сгенерированный массив: ");
  for (int i = 0; i < n; i++) {
    numbers[i] = rand() % 9000 + 1000;
    printf("%d ", numbers[i]);
  }
  printf("\n");

  int count = 0;
  for (int i = 0; i < n; i++) {
    int digits[10] = {0};
    int num = numbers[i];
    int unique = 1;

    while (num > 0) {
      int d = num % 10;
      if (digits[d]) {
        unique = 0;
        break;
      }
      digits[d] = 1;
      num /= 10;
    }

    if (unique)
      count++;
  }

  printf("Количество чисел без повторяющихся цифр: %d\n", count);
  sleep(1);
}

struct Date {
  int year, month, day;
};

struct ABON {
  char name[50];
  char phone[15];
  struct Date connect_date;
  float pay;
  float balance;
};

void sortAbonents(struct ABON arr[], int n) {
  struct ABON temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (strcmp(arr[i].name, arr[j].name) > 0) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void task2() {
  printf("\n==== ЗАДАЧА 2: Абоненты ====\n");

  int n;
  do {
    printf("Введите количество абонентов (макс 12): ");
    scanf("%d", &n);
    if (n > 12) {
      printf("Ошибка: не больше 12 абонентов!\n");
    }
  } while (n > 12);

  struct ABON abonents[n];

  for (int i = 0; i < n; i++) {
    printf("\nАбонент %d:\n", i + 1);
    printf("ФИО: ");
    getchar();
    fgets(abonents[i].name, sizeof(abonents[i].name), stdin);
    abonents[i].name[strcspn(abonents[i].name, "\n")] = '\0';

    printf("Телефон: ");
    fgets(abonents[i].phone, sizeof(abonents[i].phone), stdin);
    abonents[i].phone[strcspn(abonents[i].phone, "\n")] = '\0';

    printf("Дата подключения (гггг мм дд): ");
    scanf("%d %d %d", &abonents[i].connect_date.year,
          &abonents[i].connect_date.month, &abonents[i].connect_date.day);

    printf("Начислено: ");
    scanf("%f", &abonents[i].pay);

    printf("Баланс: ");
    scanf("%f", &abonents[i].balance);
  }

  sortAbonents(abonents, n);

  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  int current_year = t->tm_year + 1900;

  for (int i = 0; i < n; i++) {
    int years = current_year - abonents[i].connect_date.year;
    if (years > 10) {
      abonents[i].balance += 20.0;
    }
  }

  printf("\nАбоненты с отрицательным балансом:\n");
  for (int i = 0; i < n; i++) {
    if (abonents[i].balance < 0) {
      printf("%s — %.2f руб.\n", abonents[i].name, abonents[i].balance);
    }
  }
  sleep(1);
}

struct Movie {
  char title[50];
  char director[50];
  int year;
  char country[30];
  float price;
  char genre[20];
};

void task3() {
  printf("\n==== ЗАДАЧА 3: Детские фильмы ====\n");

  int n;
  do {
    printf("Введите количество фильмов (макс 5): ");
    scanf("%d", &n);
    if (n > 5) {
      printf("Ошибка: не больше 5 фильмов!\n");
    }
  } while (n > 5);

  struct Movie movies[n];
  for (int i = 0; i < n; i++) {
    printf("\nФильм %d:\n", i + 1);
    getchar();

    printf("Название: ");
    fgets(movies[i].title, sizeof(movies[i].title), stdin);
    movies[i].title[strcspn(movies[i].title, "\n")] = '\0';

    printf("Режиссёр: ");
    fgets(movies[i].director, sizeof(movies[i].director), stdin);
    movies[i].director[strcspn(movies[i].director, "\n")] = '\0';

    printf("Год выпуска: ");
    scanf("%d", &movies[i].year);

    getchar();
    printf("Страна: ");
    fgets(movies[i].country, sizeof(movies[i].country), stdin);
    movies[i].country[strcspn(movies[i].country, "\n")] = '\0';

    printf("Стоимость: ");
    scanf("%f", &movies[i].price);

    getchar();
    printf("Жанр: ");
    fgets(movies[i].genre, sizeof(movies[i].genre), stdin);
    movies[i].genre[strcspn(movies[i].genre, "\n")] = '\0';
  }

  printf("\nДетские фильмы после 2018 года:\n");
  for (int i = 0; i < n; i++) {
    if (strcmp(movies[i].genre, "детский") == 0 && movies[i].year > 2018) {
      printf("%s (%d) — %s\n", movies[i].title, movies[i].year,
             movies[i].country);
    }
  }
  sleep(1);
}

int main() {
  task1();
  task2();
  task3();
  return 0;
}
