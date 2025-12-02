#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

float sorttime[6];
int sortoper[6];
int quickcom = 0, quickoper = 0, mergecom = 0, mergeoper = 0;

void hello() {
	printf("0. Выход\n");
	printf("1. Создание массива\n");
	printf("2. Линейный поиск\n");
	printf("3. Бинарный поиск\n");
	printf("4. Пузырьковая сортировка\n");
	printf("5. Сортировка выбором\n");
	printf("6. Сортировка вставками\n");
	printf("7. Сортировка подсчётом\n");
	printf("8. Быстрая сортировка\n");
	printf("9. Сортировка слиянием\n");
	printf("10. Сравнение сортировок\n");
	printf("Ваш выбор: ");

}

void output(int* m, int n) {
	for (int i = 0; i < n; i++) {
		printf("| %d ", m[i]);
	}
	printf("|\n");
}

int* arr(int* m, int* n) {
	int a, b, buff;
	if (m != NULL) {
		free(m);
	}
	printf("Введите размер массива: ");
	scanf_s("%d", n);
	m = (int*)malloc((*n) * sizeof(int));
	if ((*n) > 10 && (*n) < 201) {
		printf("Введите левую границу значений элементов массива: ");
		scanf_s("%d", &a);
		printf("Введите правую границу значений элементов массива: ");
		scanf_s("%d", &b);
		if (a > b) {
			buff = a;
			a = b;
			b = buff;
		}
		for (int i = 0; i < (*n); i++) {
			m[i] = a + rand() % (b - a + 1);
		}
	}
	else if ((*n) > 200) {
		printf("Максимальное кол-во элементов в массиве не может превышать 200\n");
		return arr(m, n);
	}
	else {
		printf("Введите элементы массива: ");
		for (int i = 0; i < (*n); i++) {
			scanf_s("%d", &m[i]);
		}
	}
	return m;
}

int* arr2(int* m, int n) {
	int* mass = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		mass[i] = m[i];
	}
	return mass;
}

int* sortarr(int* m, int n) {
	int buff;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (m[j] > m[j + 1]) {
				buff = m[j];
				m[j] = m[j + 1];
				m[j + 1] = buff;
			}
		}
	}
	return m;
}

void linear(int* m, int n) {
	int el, flag = 0, com = 0;
	printf("Введите элемент, который вы хотите найти: ");
	scanf_s("%d", &el);
	for (int i = 0; i < n; i++) {
		com++;
		if (el == m[i]) {
			flag = 1;
			printf("Элемент %d стоит на позиции %d\n", el, i);
			break;
		}
	}
	if (flag == 0) {
		printf("Такого элемента нет в массиве\n");
	}
	printf("Количество проверок: %d\n", com);
}

void binear(int* mass, int n) {
	int first = 0, last = n - 1, mid, el, com = 0, flag = 0;
	printf("Введите элемент, который хотите найти: ");
	scanf_s("%d", &el);
	while (first <= last) {
		mid = (first + last) / 2;
		com++;
		if (mass[mid] == el) {
			flag = 1;
			printf("Элемент %d стоит на позиции %d\n", el, mid);
			break;
		}
		com++;
		if (el > mass[mid]) {
			first = mid + 1;
		}
		else {
			last = mid - 1;
		}
	}
	if (flag == 0) {
		printf("Такого элемента нет в массиве\n");
	}
	printf("Количество сравнений: %d\n", com);
}

void bubble(int* m, int n) {
	int buff, oper = 0, com = 0;
	int* arr = arr2(m, n);
	clock_t start = clock();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			com++;
			if (arr[j] > arr[j + 1]) {
				buff = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = buff;
				oper++;
			}
		}
	}
	clock_t end = clock();
	output(arr, n);
	printf("Количество операций: %d\n", oper);
	printf("Количество сравнений: %d\n", com);
	printf("Time: %.6f\n", (float)(end - start) / CLOCKS_PER_SEC);
	sortoper[0] = oper + com;
	sorttime[0] = (float)(end - start) / CLOCKS_PER_SEC;
	free(arr);
}

void choise(int* m, int n) {
	int imin, buff, oper = 0, com = 0;
	int* arr = arr2(m, n);
	clock_t start = clock();
	for (int i = 0; i < n; i++) {
		imin = i;
		for (int j = i; j < n; j++) {
			com++;
			if (arr[imin] > arr[j]) {
				imin = j;
			}
		}
		buff = arr[imin];
		arr[imin] = arr[i];
		arr[i] = buff;
		oper++;
	}
	clock_t end = clock();
	output(arr, n);
	printf("Количество операций: %d\n", oper);
	printf("Количество сравнений: %d\n", com);
	printf("Time: %.6f\n", (float)(end - start) / CLOCKS_PER_SEC);
	sortoper[1] = oper + com;
	sorttime[1] = (float)(end - start) / CLOCKS_PER_SEC;
	free(arr);
}

void insert(int* m, int n) {
	int copy, pos, oper = 0, com = 0;
	int* arr = arr2(m, n);
	clock_t start = clock();
	for (int i = 1; i < n; i++) {
		pos = i;
		for (int j = 0; j < i; j++) {
			com++;
			if (arr[i] <= arr[j]) {
				pos = j;
				break;
			}
		}
		copy = arr[i];
		for (int j = i - 1; j >= pos; j--) {
			arr[j + 1] = arr[j];
		}
		arr[pos] = copy;
		oper++;
	}
	clock_t end = clock();
	output(arr, n);
	printf("Количество операций: %d\n", oper);
	printf("Количество сравнений: %d\n", com);
	printf("Time: %.6f\n", (float)(end - start) / CLOCKS_PER_SEC);
	sortoper[2] = oper + com;
	sorttime[2] = (float)(end - start) / CLOCKS_PER_SEC;
	free(arr);
}

void count(int* m, int n) {
	int max = m[0], oper = 0;
	for (int i = 0; i < n; i++) {
		if (max <= m[i]) {
			max = m[i];
		}
	}

	int* count = arr2(m, max + 1);
	int* arr = arr2(m, n);
	clock_t start = clock();
	for (int i = 0; i < max + 1; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		count[m[i]]++;
	}
	int k = 0;
	for (int i = 0; i <= max; i++) {
		for (int j = 0; j < count[i]; j++) {
			oper++;
			arr[k++] = i;
		}
	}
	clock_t end = clock();
	output(arr, n);
	printf("Количество опреаций: %d\n", oper);
	printf("Time: %.6f\n", (float)(end - start) / CLOCKS_PER_SEC);
	sortoper[3] = oper;
	sorttime[3] = (float)(end - start) / CLOCKS_PER_SEC;
	free(count);
	free(arr);
}

void quick(int* arr, int first, int last) {
	int f = first, l = last, mid = arr[(first + last) / 2], tmp;
	while (f < l) {
		while (arr[f] < mid) {
			quickcom++;
			f++;
		}
		while (arr[l] > mid) {
			quickcom++;
			l--;
		}
		if (f <= l) {
			tmp = arr[f];
			arr[f] = arr[l];
			arr[l] = tmp;
			quickoper++;
			f++; l--;
		}
	}
	if (first < l) {
		quick(arr, first, l);
	}
	if (f < last) {
		quick(arr, f, last);
	}
}

void merge(int* m, int* arr, int first, int mid, int last) {
	int i = first, j = mid + 1, k = first;
	while (i <= mid && j <= last) {
		mergecom++;
		if (m[i] <= m[j]) {
			mergeoper++;
			arr[k] = m[i];
			i++;
			k++;
		}
		else {
			mergeoper++;
			arr[k] = m[j];
			k++;
			j++;
		}
	}
	if (i > mid) {
		while (j <= last) {
			mergeoper++;
			arr[k] = m[j];
			k++;
			j++;
		}
	}
	if (j > last) {
		while (i <= mid) {
			mergeoper++;
			arr[k] = m[i];
			k++;
			i++;
		}
	}
	for (int i = first; i <= last; i++) {
		m[i] = arr[i];
		mergeoper++;
	}
}

void mergesort(int* m, int* arr, int first, int last) {
	if (last == first) return;
	int mid = (first + last) / 2;
	mergesort(m, arr, first, mid);
	mergesort(m, arr, mid + 1, last);
	merge(m, arr, first, mid, last);
}

void info() {
	printf("Сортировка  |  Время  |   Операции   \n");
	printf("-------------------------------------\n");
	printf("Пузырьковая |%.7f| %d\n", sorttime[0], sortoper[0]);
	printf("-------------------------------------\n");
	printf("Выбором     |%.7f| %d\n", sorttime[1], sortoper[1]);
	printf("-------------------------------------\n");
	printf("Вставками   |%.7f| %d\n", sorttime[2], sortoper[2]);
	printf("-------------------------------------\n");
	printf("Подсчётом   |%.7f| %d\n", sorttime[3], sortoper[3]);
	printf("-------------------------------------\n");
	printf("Быстрая     |%.7f| %d\n", sorttime[4], sortoper[4]);
	printf("-------------------------------------\n");
	printf("Слиянием    |%.7f| %d\n", sorttime[5], sortoper[5]);
	printf("-------------------------------------\n");
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "rus");
	int* m = nullptr, n, code, turn, flag = 0, f, * sortm = nullptr, * arrm = nullptr;
	clock_t start, end;
	do {
		hello();
		turn = scanf_s("%d", &code);
		switch (code) {
		case 0: break;
		case 1: flag = 1; f = 0;
			m = arr(m, &n);
			sortm = arr2(m, n);
			sortarr(sortm, n);
			for (int i = 0; i < 6; i++) {
				sorttime[i] = 0;
				sortoper[i] = 0;
			}
			quickcom = 0; quickoper = 0; mergecom = 0; mergeoper = 0;
			output(m, n);
			break;

		case 2: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  linear(m, n); break;

		case 3:
			if (flag == 0) {
				printf("Сначала заполните массив\n");
				break;
			}
			if (f == 0) {
				printf("Сначала отсортируйте массив\n");
				break;
			}
			binear(sortm, n);
			break;

		case 4: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  bubble(m, n); f++; break;

		case 5: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  choise(m, n); f++; break;

		case 6: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  insert(m, n); f++; break;

		case 7: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  count(m, n); f++; break;

		case 8: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  f++;
			  arrm = arr2(m, n);
			  start = clock();
			  quick(arrm, 0, n - 1);	
			  end = clock();
			  output(arrm, n);
			  sortoper[4] = quickoper + quickcom;
			  sorttime[4] = (float)(end - start) / CLOCKS_PER_SEC;
			  printf("Количество операций: %d\n", quickoper);
			  printf("Количество сравнений: %d\n", quickcom);
			  printf("Time: %.6f\n", (float)(end - start) / CLOCKS_PER_SEC);
			  free(arrm);
			  break;

		case 9: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  f++;
			  arrm = arr2(m, n);
			  start = clock();
			  mergesort(m, arrm, 0, n - 1);
			  end = clock();
			  output(arrm, n);
			  sortoper[5] = mergeoper + mergecom;
			  sorttime[5] = (float)(end - start) / CLOCKS_PER_SEC;
			  printf("Количество операций: %d\n", mergeoper);
			  printf("Количество сравнений: %d\n", mergecom);
			  printf("Time: %.6f\n", (float)(end - start) / CLOCKS_PER_SEC);
			  free(arrm);
			  break;

		case 10:  if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			   if (f != 6) {
				   printf("Сначала опробуйте все сортировки, прежде чем их сравнивать\n");
				   break;
			   }
			   info();
			   break;

		default: if (turn == 0) {
			printf("Ошибка! Можно вводить только числа\n");
			while (getchar() != '\n');
		}
			   if (code > 10 || code < 0) {
				   printf("Можно вводить числа только от 1 до 10\n");
			   }
			   break;
		}
	} while (code != 0);

	if (m != NULL) {
		free(m);
	}
	if (sortm != NULL) {
		free(sortm);
	}
	return 0;
}