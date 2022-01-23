from django.db import models
from django.urls import reverse
from django.db.models import IntegerField, Model
from django.core.validators import MaxValueValidator, MinValueValidator


# Create your models here.
class Trainer(models.Model):
    Name= models.CharField(max_length=120)
    Surname = models.CharField(max_length=120)
    City = models.CharField(max_length=120)
    # Basinda 0 olmadan girilecek
    Phone = models.CharField(max_length=10)
    Mail = models.EmailField(max_length=120)
    gender_dict = [
        (True, 'Erkek'),
        (False, 'Kadın')
    ]
    Gender = models.BooleanField(blank=False, null=False, choices=gender_dict)
    Address = models.TextField()
    Work_Experience = models.TextField()
    image = models.FileField(null=True,blank=True)
    Birth_Date = models.DateField()
    approval_dict = [
        (True, 'Onaylı'),
        (False, 'Onaylanmamış')
    ]
    is_approved = models.BooleanField(default=False, verbose_name = 'Onay', choices=approval_dict)
    User_ID = models.ForeignKey('auth.User', related_name='trainers', on_delete=models.CASCADE, blank=True, null=True, verbose_name='Kullanıcı Hesabı')

    def __str__(self):
        return self.Name + ' ' + self.Surname

    def get_absolute_url(self):
        return reverse('trainer:detail', kwargs={'id': self.id})

    def get_send_message_url(self):
        return reverse('messaging:send_message', kwargs={'trainer_id': self.id})

class Comment(models.Model):
    trainer = models.ForeignKey('trainer.Trainer', related_name='comments', on_delete=models.CASCADE, verbose_name='Gönderi')
    name = models.CharField(max_length=200, verbose_name='Başlık')
    content = models.TextField(verbose_name='Yorum')
    created_date = models.DateTimeField(auto_now_add=True, verbose_name='Oluşturulma Tarihi')

class CalendarEvent(models.Model):
    trainer = models.ForeignKey('trainer.Trainer', related_name='calendarevent', on_delete=models.CASCADE, verbose_name='Trainer')
    day_of_week_dict = [
        (0, 'Monday'),
        (1, 'Tuesday'),
        (2, 'Wednesday'),
        (3, 'Thursday'),
        (4, 'Friday'),
        (5, 'Saturday'),
        (6, 'Sunday'),
    ]
    day_of_week = models.IntegerField(default=0, verbose_name='Day of week', choices=day_of_week_dict)
    start_time = models.IntegerField(validators=[
            MaxValueValidator(23),
            MinValueValidator(0)
        ])
    def __str__(self):
        return self.trainer.Name + ' ' + self.trainer.Surname + ' | ' + str(self.day_of_week_dict[self.day_of_week][1] ) + ' | ' + str(self.start_time) + ":00"

class Reservation(models.Model):
    event = models.ForeignKey('CalendarEvent', related_name='reservation', on_delete=models.CASCADE, verbose_name='Calendar Event')
    trainer = models.ForeignKey('Trainer', related_name='reservation', on_delete=models.CASCADE, verbose_name='Trainer')
    customer = models.ForeignKey('auth.User', related_name='reservation', on_delete=models.CASCADE, blank=True, null=True, verbose_name='User')
    date_time = models.DateField( verbose_name='Reservation Date')

    def __str__(self):
        return self.customer.get_username() + ' ' + str(self.date_time) + " " + str(self.event.start_time) +":00"
