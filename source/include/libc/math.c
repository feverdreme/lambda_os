int ceildiv(int a, int b) {
    if (a % b == 0) return a / b;
    else return a / b + 1;
}