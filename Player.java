package com.example.project2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

//import static jdk.nashorn.internal.objects.NativeSet.add;

/*Класс игрока*/
public class Player extends JFrame{
    private JButton buttonVin;
    private JButton buttonLos;
    private JLabel panelNamePlayer;
    private JLabel panelResultPlayer;

    private int resultUserPlayers;
    private String nameUserPlayer;

    public Player(int result, String name) {
        this.resultUserPlayers=result;
        this.nameUserPlayer=name;

        panelNamePlayer = new JLabel("Name: " + nameUserPlayer);
        panelResultPlayer = new JLabel("Result: " + resultUserPlayers);
        buttonVin = new JButton("Vinner");
        buttonLos = new JButton("Loser");

        JPanel displayGame = new JPanel(new FlowLayout());
        displayGame.setLayout(new BoxLayout(displayGame, BoxLayout.LINE_AXIS));
        add(panelNamePlayer, BorderLayout.NORTH);
        add(panelResultPlayer, BorderLayout.CENTER);
        displayGame.add(buttonVin, BorderLayout.CENTER);
        displayGame.add(buttonLos, BorderLayout.CENTER);
        add(displayGame, BorderLayout.SOUTH);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //interfaceGame();
    }
    public int sumResultUserPlayers(){
        resultUserPlayers+=1;
        return resultUserPlayers;
    }

    public int unsumResultPlayers(){
        resultUserPlayers-=1;
        return resultUserPlayers;
    }

    public String getNameUserPlayer() {
        return nameUserPlayer;
    }

    public int getResultUserPlayers(){
        return this.resultUserPlayers;
    }

//    private void interfaceGame(){
//         buttonVin.addActionListener(new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 panelResultPlayer.setText("Result: "+sumResultUserPlayers());
//             }
//         });
//         buttonLos.addActionListener(new ActionListener() {
//             @Override
//             public void actionPerformed(ActionEvent e) {
//                 panelResultPlayer.setText("Result: "+unsumResultPlayers());
//             }
//         });
//    }
}
