package com.company;

public class Main {
    private static int x;
    private static int y;
    private static int r1;
    private static int r2;

    public static void main(String[] args) {
        for (int i = 0; true; i += 1) {
            // This was changed to 1 instead of 0 because 0 is the default value for ints, so it was harder to see if
            // there was anything wrong.
            Main.x = Main.y = Main.r1 = Main.r2 = 1;

            Thread t1 = new Thread(() -> {
                synchronized ((Object)Main.x) {
                    Main.x = 2;
                }

                Main.r1 = Main.y;
            });

            Thread t2 = new Thread(() -> {
                synchronized ((Object)Main.y) {
                    Main.y = 2;
                }

                Main.r2 = Main.x;
            });

            t1.start();
            t2.start();

            try {
                t2.join();
                t1.join();
            } catch(InterruptedException e) {
                System.out.println("Got an interrupt from one of the threads, this should never happen!");
                System.exit(-1);
            }

            if (Main.r1 == 1 && Main.r2 == 1) {
                System.out.println("Found condition in iteration " + i);
                System.exit(-1);
            }
        }
    }
}
