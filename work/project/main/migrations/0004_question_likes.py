# Generated by Django 2.0.7 on 2018-09-11 20:13

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('main', '0003_question_summary'),
    ]

    operations = [
        migrations.AddField(
            model_name='question',
            name='likes',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
    ]
