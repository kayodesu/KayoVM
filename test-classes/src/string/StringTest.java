package string;

/**
 * Status: Pass
 */
public class StringTest {
    
    public static void main(String[] args) {
        String s1 = new String("abc1");
        System.out.println(s1);
        String s2 = "abc1";

        int x = 1;
        String s3 = "abc" + x;
        System.out.println(s3);
        if (s1.equals(s3)) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }

        s3 = s3.intern();
        String s4 = "abc1";
        if (s3 == s4) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }
    }

}
