#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int quickoper = 0, quickcom = 0, mergeoper = 0, mergecom = 0;

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

void output(int* m, int s) {
	for (int i = 0; i < s; i++) {
		printf("| %d ", m[i]);
	}
	printf("|\n");
}

void result(int *m, int s, int oper, int com, float time) {
	if (s < 201) output(m, s);
	printf("Количество обменов: %d\n", oper);
	printf("Количество сравнений: %d\n", com);
	printf("Время %.7f\n", time);
}

int* arr(int* m, int* s) {
	int a, b, buff;
	if (m != NULL) {
		free(m);
	}
	printf("Введите размер массива: ");
	scanf_s("%d", s);
	m = (int*)malloc((*s) * sizeof(int));
	if ((*s) > 10) {
		printf("Введите левую границу значений элементов массива: ");
		scanf_s("%d", &a);
		printf("Введите правую границу значений элементов массива: ");
		scanf_s("%d", &b);
		if (a > b) {
			buff = a;
			a = b;
			b = buff;
		}
		for (int i = 0; i < (*s); i++) {
			m[i] = a + rand() % (b - a + 1);
		}
	}
	else {
		printf("Введите элементы массива: ");
		for (int i = 0; i < (*s); i++) {
			scanf_s("%d", &m[i]);
		}
	}
	if ((*s) > 200) {
		for (int i = 0; i < 200; i++) {
			printf("| %d ", m[i]);
		}
		printf("|\n");
	}
	else {
		for (int i = 0; i < (*s); i++) {
			printf("| %d ", m[i]);
		}
		printf("|\n");
	}
	return m;
}

int* arr2(int* m, int s) {
	int* mass = (int*)malloc(sizeof(int) * s);
	for (int i = 0; i < s; i++) {
		mass[i] = m[i];
	}
	return mass;
}

void linear(int* m, int s) {
	int el, flag = 0, com = 0;
	printf("Введите элемент, который вы хотите найти: ");
	scanf_s("%d", &el);
	for (int i = 0; i < s; i++) {
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

void binear(int* mass, int s) {
	int first = 0, last = s - 1, mid, el, com = 0, flag = 0;
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

void bubble(int* m, int s, int* bubboper, int*bubbcom) {
	int buff, oper = 0, com = 0;
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s - 1; j++) {
			com++;
			if (m[j] > m[j + 1]) {
				buff = m[j];
				m[j] = m[j + 1];
				m[j + 1] = buff;
				oper++;
			}
		}
	}
	*bubboper = oper;
	*bubbcom = com;
}

void choise(int* m, int s, int* chooper, int* chocom) {
	int imin, buff, oper = 0, com = 0;
	for (int i = 0; i < s; i++) {
		imin = i;
		for (int j = i; j < s; j++) {
			com++;
			if (m[imin] > m[j]) {
				imin = j;
			}
		}
		buff = m[imin];
		m[imin] = m[i];
		m[i] = buff;
		oper++;
	}
	*chooper = oper;
	*chocom = com;
}

void insert(int* m, int s, int* insoper, int* inscom) {
	int copy, pos, oper = 0, com = 0;
	for (int i = 1; i < s; i++) {
		pos = i;
		for (int j = 0; j < i; j++) {
			com++;
			if (m[i] <= m[j]) {
				pos = j;
				break;
			}
		}
		copy = m[i];
		for (int j = i - 1; j >= pos; j--) {
			m[j + 1] = m[j];
		}
		m[pos] = copy;
		oper++;
	}
	*insoper = oper;
	*inscom = com;
}

void count(int* m, int s, int* countoper, int* countcom) {
	int max = m[0], min = m[0], range = 0, oper = 0;
	for (int i = 0; i < s; i++) {
		if (max <= m[i]) {
			max = m[i];
		}
		if (min >= m[i]) {
			min = m[i];
		}
	}
	if (min < 0) {
		max = max - min;
	}
	int* count = arr2(m, max + 1);
	for (int i = 0; i < max + 1; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < s; i++) {
		count[m[i] - min]++;
	}
	int k = 0;
	for (int i = 0; i <= max; i++) {
		for (int j = 0; j < count[i]; j++) {
			oper++;
			m[k++] = i + min;
		}
	}
	*countoper = oper;
	free(count);
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

void info(int obub, float tbub, int ocho, float tcho, int oins, float tins, int ocount, float tcount, float tquick, float tmerge) {
	printf("Сортировка  |  Время  |   Операции   \n");
	printf("-------------------------------------\n");
	printf("Пузырьковая |%.7f| %d\n", tbub, obub);
	printf("-------------------------------------\n");
	printf("Выбором     |%.7f| %d\n", tcho, ocho);
	printf("-------------------------------------\n");
	printf("Вставками   |%.7f| %d\n", tins, oins);
	printf("-------------------------------------\n");
	printf("Подсчётом   |%.7f| %d\n", tcount, ocount);
	printf("-------------------------------------\n");
	printf("Быстрая     |%.7f| %d\n", tquick, quickoper + quickcom);
	printf("-------------------------------------\n");
	printf("Слиянием    |%.7f| %d\n", tmerge, mergeoper + mergecom);
	printf("-------------------------------------\n");
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "rus");
	int* m = nullptr, s, code, turn, flag = 0, f, * arrm = nullptr, * arrm2 = nullptr;
	int bubbcom, bubboper, chooper, chocom, inscom, insoper, countcom, countoper, musor = 0;
	float bubbtime, chotime, instime, counttime, quicktime, mergetime;
	int case1, case2, case3, case4, case5, case6;
	clock_t start, end;
	do {
		hello();
		turn = scanf_s("%d", &code);
		switch (code) {
		case 0: break;
		case 1: flag = 1; f = 0;
			  case1 = case2 = case3 = case4 = case5 = case6 = 0;
			  m = arr(m, &s);
			  break;

		case 2: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  linear(m, s); break;

		case 3:if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			if (f == 0) {
				printf("Сначала отсортируйте массив\n");
				break;
			}
			  musor = 0;
			  arrm = arr2(m, s);
			  insert(arrm, s, &musor, &musor);
			  binear(arrm, s);
			  free(arrm);
			  break;

		case 4: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  bubbcom = bubboper = 0; bubbtime = 0; case1 = 1;
			  arrm = arr2(m, s);
			  start = clock();
			  bubble(arrm, s, &bubboper, &bubbcom);
			  end = clock();
			  bubbtime = ((float)(end - start)) / CLOCKS_PER_SEC; f++;
			  result(arrm, s, bubboper, bubbcom, bubbtime);
			  free(arrm);
			  break;

		case 5: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}		
			  chooper = chocom = 0; chotime = 0; case2 = 1;
			  arrm = arr2(m, s);
			  start = clock();
			  choise(arrm, s, &chooper, &chocom);
			  end = clock();
			  chotime = ((float)(end - start)) / CLOCKS_PER_SEC; f++;
			  result(arrm, s, chooper, chocom, chotime);
			  free(arrm);
			  break;

		case 6: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  inscom = insoper = 0; instime = 0; case3 = 1;
			  arrm = arr2(m, s);
			  start = clock();
			  insert(arrm, s, &insoper, &inscom);
			  end = clock();
			  instime = ((float)(end - start)) / CLOCKS_PER_SEC; f++;
			  result(arrm, s, insoper, inscom, instime);
			  free(arrm);
			  break;

		case 7: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  countcom = countoper = 0; counttime = 0; case4 = 1;
			  arrm = arr2(m, s);
			  start = clock();
			  count(arrm, s, &countoper, &countcom);
			  end = clock();
			  counttime = ((float)(end - start)) / CLOCKS_PER_SEC; f++;
			  result(arrm, s, countoper, countcom, counttime);
			  free(arrm);
			  break;

		case 8: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  quickoper = quickcom = 0; quicktime = 0; case5 = 1;
			  arrm = arr2(m, s);
			  start = clock();
			  quick(arrm, 0, s - 1);	
			  end = clock();
			  quicktime = ((float)(end - start)) / CLOCKS_PER_SEC; f++;
			  result(arrm, s, quickoper, quickcom, quicktime);
			  free(arrm);
			  break;

		case 9: if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			  mergeoper = mergecom = 0;	mergetime = 0; case6 = 1;
			  arrm = arr2(m, s);
			  arrm2 = arr2(m, s);
			  start = clock();
			  mergesort(arrm, arrm2, 0, s - 1);
			  end = clock();
			  mergetime = ((float)(end - start)) / CLOCKS_PER_SEC; f++;
			  result(arrm, s, mergeoper, mergecom, mergetime);
			  free(arrm);
			  free(arrm2);
			  break;

		case 10:  if (flag == 0) {
			printf("Сначала заполните массив\n");
			break;
		}
			   if ((case1==0) || (case2==0) || (case3==0) || (case4==0) || (case5==0) || (case6==0)) {
				   printf("Сначала опробуйте все сортировки, прежде чем их сравнивать\n");
				   break;
			   }
			   info(bubboper+bubbcom,bubbtime,chooper+chocom,chotime,insoper+inscom,instime,countoper+countcom,counttime,quicktime,mergetime);
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
	return 0;
}