class Fibo {
  public static void main(String[] args) {
    int N = 1000;
    double a = 0.0;
    double b = 1.0;
    double temp;

    for (int i = 0; i < N; i++) {
      temp = b;
      b += a;
      a = temp;
    }
    System.out.println(a);
  }
}
