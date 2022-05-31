package com.guiguli.string_ArrayList;

public class Movie {
    private String name;
    private double score;
    private String actotor;

    public Movie(String name, double score, String actotor) {
        this.name = name;
        this.score = score;
        this.actotor = actotor;
    }

    public  Movie(){

    }
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getScore() {
        return score;
    }

    public void setScore(double score) {
        this.score = score;
    }

    public String getActotor() {
        return actotor;
    }

    public void setActotor(String actotor) {
        this.actotor = actotor;
    }

    @Override
    public String toString() {
        return "Movie{" +
                "name='" + name + '\'' +
                ", score=" + score +
                ", actotor='" + actotor + '\'' +
                '}';
    }
}