from django.db import models

class Feedback(models.Model):
    Name = models.CharField(max_length=120)
    Surname = models.CharField(max_length=120)
    Mail = models.EmailField(max_length=120)
    Comment = models.TextField(verbose_name='Feedback')

    def __str__(self):
        return self.Name + ' ' + self.Surname
