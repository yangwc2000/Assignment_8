// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"

AMineItem::AMineItem()
{
	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30.0f;
	ItemType = "Mine";

}

void AMineItem::ActivateItem(AActor* Activator)
{
	DestroyItem();
}