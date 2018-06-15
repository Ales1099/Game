package com.example.project2;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Scanner;

/*Интерфейс игры*/
public class Game extends JFrame {

      private final static int numberPlayers=2;
      private Player[] player = new Player[numberPlayers];

      private JButton[] buttonVin=new JButton[numberPlayers];
      private JButton[] buttonLos=new JButton[numberPlayers];
      private JLabel[] namePlayer=new JLabel[numberPlayers];
      private JLabel[] resultPlayer = new JLabel[numberPlayers];
      private JPanel panel = new JPanel();

      private JButton buttonVinnerPlayer;
      private JLabel nameVinnerPlayer;
      private JPanel panelVinnerPlayer;

      public Game(){
          Scanner in= new Scanner(System.in);
          for(int u=1; u<=numberPlayers; ++u) {
              System.out.print("Введите имя "+u+" игрока : ");
              String name=in.nextLine();
              player[u-1] = new Player(0, name);

          }

          JFrame frame= new JFrame();

          frame.setSize(200,500);
          frame.setLayout(new GridLayout());

          for(int i=0; i<numberPlayers; ++i) {

              namePlayer[i]=new JLabel("Name: "+player[i].getNameUserPlayer());
              resultPlayer[i]= new JLabel("Result: "+player[i].getResultUserPlayers());
              buttonVin[i]= new JButton("Vinner");
              buttonLos[i]= new JButton("Loser");

              panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
              panel.add(namePlayer[i], BorderLayout.NORTH);
              panel.add(resultPlayer[i], BorderLayout.NORTH);
              panel.add(buttonVin[i], BorderLayout.NORTH);
              panel.add(buttonLos[i], BorderLayout.NORTH);

              interfaceGame(i);

              frame.add(panel);
          }

          panelVinnerPlayer=new JPanel();
          nameVinnerPlayer=new JLabel("Vinner: " + "");
          buttonVinnerPlayer=new JButton("Vinner");
          panelVinnerPlayer.add(nameVinnerPlayer, BorderLayout.SOUTH);
          panelVinnerPlayer.add(buttonVinnerPlayer, BorderLayout.SOUTH);
          vinnerPalyer();
          frame.add(panelVinnerPlayer);

          frame.setVisible(true);
      }

    private void interfaceGame(int num){
        buttonVin[num].addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                resultPlayer[num].setText("Result: "+player[num].sumResultUserPlayers());
            }
        });
        buttonLos[num].addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                resultPlayer[num].setText("Result: "+player[num].unsumResultPlayers());
            }
        });}
    private void vinnerPalyer(){
       buttonVinnerPlayer.addActionListener(new ActionListener() {
          @Override
          public void actionPerformed(ActionEvent e) {
             int max=-1001;
             int positonPlayer=0;
             for(int u=0; u<numberPlayers; ++u){
               if(player[u].getResultUserPlayers()>max) { max=player[u].getResultUserPlayers(); positonPlayer=u;}
             }
             nameVinnerPlayer.setText("Vinner: "+ player[positonPlayer].getNameUserPlayer());
            }
         });
        }


}
