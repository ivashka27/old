# Generated by Django 2.0.7 on 2018-12-11 16:05

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('main', '0017_auto_20181118_1153'),
    ]

    operations = [
        migrations.AddField(
            model_name='user',
            name='email',
            field=models.TextField(default=''),
        ),
    ]
